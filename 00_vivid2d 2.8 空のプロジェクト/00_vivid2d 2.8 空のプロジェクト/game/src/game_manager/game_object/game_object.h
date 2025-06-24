#pragma once
#include "../../component/component.h"

#include "../../mathematics/mathematics.h"
#include "../../utility/utility.h"

#include <memory>    // std::shared_ptr のため
#include <map>       // コンポーネント管理のための std::map のため
#include <typeindex> // コンポーネントの型情報をキーとして使うため
#include <typeinfo>  // typeid を使うため
#include <cassert>   // static_assert のため


// CGameObject クラス
// このクラスがすべてのゲーム内エンティティの基底となる
class CGameObject
{
public:
    CGameObject(); // コンストラクタを定義

    virtual ~CGameObject(); // デストラクタは virtual にしておく

    // --- コンポーネント管理メソッド ---

    // コンポーネントを追加する
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        if (HasComponent<T>())
        {
            return GetComponent<T>();
        }

        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
        m_Components[typeid(T)].push_back(component); // マップに登録
        component->OnAttach(this); // アタッチ時に自身のポインタを渡す
        return component;
    }

    // 特定の型のコンポーネントをすべて取得する
    template<typename T>
    std::vector<std::shared_ptr<T>> GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        std::vector<std::shared_ptr<T>> result;
        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end())
        {
            for (const auto& comp : it->second)
            {
                if (auto casted_comp = std::dynamic_pointer_cast<T>(comp))
                {
                    result.push_back(casted_comp);
                }
            }
        }
        return result;
    }

    // 特定のコンポーネントを持っているか確認する
    template<typename T>
    bool HasComponent() const
    {
        return m_Components.count(typeid(T)) > 0; //
    }

    // コンポーネントを削除する
    template<typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must inherit from IComponent");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end())
        {
            // it->second はコンポーネントのベクター
            // 各コンポーネントの OnDetach を呼び出す
            for (auto& component : it->second)
            {
                component->OnDetach(this);
            }

            m_Components.erase(it); // マップから該当する型のベクターをすべて削除
        }
    }

    // --- ライフサイクルメソッド ---
    virtual void Initialize(); //
    virtual void Update(float delta_time); // delta_time を引数に追加
    virtual void Draw(); //
    virtual void Finalize(); //

    // --- 基本的なデータへのアクセス ---
    virtual const CVector3& GetPosition() const { return m_Position; } //
    virtual void SetPosition(const CVector3& position) { m_Position = position; } //

    virtual CTransform GetTransform() const { return m_Transform; } //
    virtual void SetTransform(const CTransform& transform) { m_Transform = transform; } //

    virtual bool IsActive() const { return m_IsActive; } //
    virtual void SetActive(bool active) { m_IsActive = active; } //
protected:

    CVector3    m_Position;
    CTransform  m_Transform;

    bool        m_IsActive; //!< アクティブ/非アクティブ状態を管理するフラグ
private:
    // この GameObject がアタッチしているコンポーネントを管理するマップ
    // キーはコンポーネントの型情報 (typeid(T))、値は shared_ptr<IComponent>
    std::map<std::type_index, std::vector<std::shared_ptr<IComponent>>> m_Components;



};