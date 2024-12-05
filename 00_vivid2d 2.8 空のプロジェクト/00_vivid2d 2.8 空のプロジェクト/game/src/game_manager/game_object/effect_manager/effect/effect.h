#pragma once

#include "vivid.h"
#include "effect_id.h"
#include "../../../../mathematics/mathematics.h"
#include "../../../../utility/utility.h"

class IEffect
{
public:
    /*!
     *  @brief      コンストラクタ
     */
    IEffect();
    /*!
     *  @brief      コンストラクタ
     */
    IEffect(const std::string& file_name, EFFECT_ID effectID);

    /*!
     *  @brief      コンストラクタ
     */
    IEffect(const std::string& file_name, EFFECT_ID effectID, float speed);

    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  width   幅
     *  @param[in]  height  高さ
     */
    IEffect(int width, int height);

    /*!
     *  @brief      デストラクタ
     */
    virtual ~IEffect(void);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  color       色
     *  @param[in]  rotation    回転値
     */
    virtual void    Initialize(const vivid::Vector2& position, unsigned int color, float rotation);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     */
    virtual void    Initialize(const CVector3& position);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  scale       拡大率
     */

    virtual void    Initialize(const CVector3& position, float scale);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  rotation    回転
     */

    virtual void    Initialize(const CVector3& position, const CVector3& rotation);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  rotation    回転
     *  @param[in]  scale       拡大率
     */

    virtual void    Initialize(const CVector3& position, const CVector3& rotation, float scale);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  rotation    回転
     *  @param[in]  scale       拡大率
     */

    virtual void    Initialize(const CVector3& position, const CVector3& rotation, const CVector3& scale);

    /*!
     *  @brief      初期化
     *
     *  @param[in]  position    位置
     *  @param[in]  rotation    回転
     *  @param[in]  scale       拡大率
     *  @param[in]  speed       再生速度
     */

    virtual void    Initialize(const CVector3& position, const CVector3& rotation, float scale, float speed);

    void	Load(const std::string& file_name);

    void    Start();
    /*!
     *  @brief      更新
     */
    virtual void    Update(void);

    /*!
     *  @brief      描画
     */
    virtual void    Draw(void);

    /*!
     *  @brief      解放
     */
    virtual void    Finalize(void);

    /*!
     *  @brief      位置取得
     *
     *  @return     位置
     */
    CVector3  GetPosition(void);

    /*!
     *  @brief      位置設定
     *
     *  @param[in]  position    位置
     */
    void            SetPosition(const CVector3& position);

    /*!
     *  @brief      回転取得
     *
     *  @return     回転
     */
    CVector3        GetRotation(void);

    /*!
     *  @brief      回転設定
     *
     *  @param[in]  position    回転
     */
    void           SetRotation(const CVector3& rotation);

    /*!
     *  @brief      アクティブフラグ取得
     *
     *  @return     アクティブフラグ
     */
    bool            GetActive(void);

    /*!
     *  @brief      アクティブフラグ設定
     *
     *  @param[in]  active  アクティブフラグ
     */
    void            SetActive(bool active);

    /*!
     *  @brief      親の位置設定
     *
     *  @param[in]  parentPos  親の位置
     */
    void            SetParentPosition(CVector3& parentPos);

    /*!
     *  @brief      エフェクトID取得
     *
     *  @return     エフェクトID
     */
    EFFECT_ID       GetEffectID(void);

    /*!
     *  @brief      エフェクトハンドル取得
     *
     *  @return     エフェクトハンドル
     */
    int             GetEffectHandle(void);

protected:
    int			            m_PlayHandle;   //!< ハンドル
    CTransform              m_Transform;    //!< トランスフォーム
    std::string             m_FileName;     //!< エフェクトのファイル名
    CVector3                m_Scale;        //!< 拡大率
    bool                    m_ActiveFlag;   //!< アクティブフラグ
    int                     m_Width;        //!< 幅
    int                     m_Height;       //!< 高さ
    vivid::Vector2          m_Position2D;   //!< 位置
    unsigned int            m_Color;        //!< 色
    vivid::Vector2          m_Anchor;       //!< 基準点
    vivid::Rect             m_Rect;         //!< 読み込み範囲
    vivid::Vector2          m_Scale2D;      //!< 2Dの拡大率
    float                   m_Rotation;     //!< 回転値
    CVector3*               m_ParentPos;    //!< 親の位置
    EFFECT_ID               m_EffectID;     //!< エフェクトID
    float                   m_Speed;        //!< 再生速度
};
