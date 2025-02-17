#pragma once
#include "..\..\..\model_manager\model\model.h"
#include "..\object.h"

enum class OBSTRUCTION_ID
{
	DOWN_1,
    UP_1,

	MAX,
};

class CBeltConveyorObstructionObject : public IObject
{
public:
    CBeltConveyorObstructionObject();
    ~CBeltConveyorObstructionObject();

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
     *  @brief      解放
     * 
     *  @param[in]  id      セットする障害物タイプのID
     */
    void    SetObstructionType(OBSTRUCTION_ID id);

private:
    static const std::string m_model_file_name_list[(int)OBSTRUCTION_ID::MAX];

    OBSTRUCTION_ID m_NowObstructionID;
};