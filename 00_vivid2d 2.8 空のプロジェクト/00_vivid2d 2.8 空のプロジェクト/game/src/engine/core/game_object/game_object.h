#pragma once
#include "../component/component.h"
#include "../../mathematics/mathematics.h"
#include "../../utility/utility.h"

#include <memory>
#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <cassert>
#include "game_types.h"
#include "../../managers/object_manager/object_id.h"

class CGameObject
{
public:

	/*!
	 * @brief      コンストラクタ
	 */
    CGameObject();

	/*!
	 * @brief      デストラクタ
	 */
    virtual ~CGameObject();

    /*!
     * @brief コンポーネントをこのゲームオブジェクトに追加
     * 
     * @param[in] T 追加するコンポーネントの型 (IComponent派生クラス)
     * @param[in] Args コンポーネントのコンストラクタに渡す引数
     * 
     * @return 生成され、追加されたコンポーネントへのポインタ
     */
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<IComponent, T>::value, "テンプレート引数 T は IComponent を継承している必要があります");

        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
        m_Components[typeid(T)].push_back(component);
        component->OnAttach(this);
        return component;
    }

    /*!
     * @brief 指定された型の最初のコンポーネントを取得
     * 
     * @param[in] T 取得したいコンポーネントの型
     * 
     * @return 見つかったコンポーネントへのポインタ なければnullptr
     */
    template<typename T>
    std::shared_ptr<T> GetComponent() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "テンプレート引数 T は IComponent を継承している必要があります");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end() && !it->second.empty())
        {
            return std::dynamic_pointer_cast<T>(it->second.front());
        }
        return nullptr;
    }

    /*!
     * @brief 指定された型の全てのコンポーネントをベクターで取得
     * 
     * @param[in] T 取得したいコンポーネントの型
     * 
     * @return 見つかったコンポーネントのポインタを格納したstd::vector
     * 見つからなかった場合は、空のベクターを返す
     */
    template<typename T>
    std::vector<std::shared_ptr<T>> GetComponents() const
    {
        static_assert(std::is_base_of<IComponent, T>::value, "テンプレート引数 T は IComponent を継承している必要があります");

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

    /*!
     * @brief 特定のコンポーネントを少なくとも1つ持っているか確認
     * 
	 * @param[in] T 確認したいコンポーネントの型
     * 
	 * @return 指定された型のコンポーネントが存在する場合はtrue、存在しない場合はfalse
     */
    template<typename T>
    bool HasComponent() const
    {
        auto it = m_Components.find(typeid(T));
        return (it != m_Components.end() && !it->second.empty());
    }

    /*!
     * @brief 指定された型のコンポーネントをすべて削除
     * 
	 * @param[in] T 削除したいコンポーネントの型
     */
    template<typename T>
    void RemoveComponent()
    {
        static_assert(std::is_base_of<IComponent, T>::value, "テンプレート引数 T は IComponent を継承している必要があります");

        auto it = m_Components.find(typeid(T));
        if (it != m_Components.end())
        {
            for (auto& component : it->second)
            {
                component->OnDetach(this);
            }
            m_Components.erase(it);
        }
    }

    // --- ライフサイクル ---
    virtual void Initialize();
    virtual void Update(float delta_time);
    virtual void Draw();
    virtual void Finalize();

    virtual bool IsActive() const { return m_IsActive; }
    virtual void Delete() { m_IsActive = false; }
    // --- ID管理 ---
    void SetID(OBJECT_ID id) { m_ID = id; }
    OBJECT_ID GetID() const { return m_ID; }

    // --- タグ管理 ---
    void SetTag(GAME_OBJECT_TAG tag) { m_Tag = tag; }
    GAME_OBJECT_TAG GetTag() const { return m_Tag; }

    // --- タグ管理 ---
    void SetCategory(FACTION_CATEGORY category) { m_Category = category; }
    FACTION_CATEGORY GetCategory() const { return m_Category; }

protected:
	bool                m_IsActive; //!< オブジェクトがアクティブかどうかを示すフラグ

private:
	std::map<std::type_index, std::vector<std::shared_ptr<IComponent>>> m_Components; //!< コンポーネントのマップ
    GAME_OBJECT_TAG     m_Tag;      //!< タグを保持するメンバー変数
    OBJECT_ID           m_ID;       //!< オブジェクトのIDを保持
	FACTION_CATEGORY    m_Category; //!< カテゴリーを保持するメンバー変数
};