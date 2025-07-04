#pragma once
#include "../../../model/model.h"
#include "..\object.h"
#include "..\..\..\..\..\utility\utility.h"
enum class OGRE_OBJECT_STATE
{
    WAIT,
    FALL,
};
class COgreObject : public IObject
{
public:
    COgreObject();
    ~COgreObject();

    /*!
     *  @brief      初期化
     *
     */
    void    Initialize(OBJECT_ID id, const CTransform& transform);

    /*!
     *  @brief      更新
     */
    void    Update(void);

    /*!
     *  @brief      描画
     */
    void    Draw(void);

    /*!
     *  @brief      解放
     */
    void    Finalize(void);

    /*!
     *  @brief      ID取得
     *
     *  @return     マークID
     */

private:
    static const float                     m_start_height;
    static const float                     m_return_height;
    static const float                     m_invisible_alpha;
    static const std::string               m_file_name;
    float                                  m_FallSpeed;
    OGRE_OBJECT_STATE           m_Daruma_FallDownObjectState;
    CTimer                                 m_Timer;
};