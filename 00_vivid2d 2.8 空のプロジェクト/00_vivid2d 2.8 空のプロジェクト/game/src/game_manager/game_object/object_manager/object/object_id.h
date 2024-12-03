#pragma once

/*!
 *  @brief      �I�u�W�F�N�gID
 */
enum class OBJECT_ID
{
    NONE,                   //!< ��
    MOON_FALL_OBJECT,       //!< ������I�u�W�F�N�g(���}�[�N)
    SUN_FALL_OBJECT,        //!< ������I�u�W�F�N�g(���z�}�[�N)
    CIRCLE_FALL_OBJECT,     //!< ������I�u�W�F�N�g(�ۃ}�[�N)
    SQUARE_FALL_OBJECT,     //!< ������I�u�W�F�N�g(�l�p�}�[�N)
    TRIANGLE_FALL_OBJECT,   //!< ������I�u�W�F�N�g(�O�p�}�[�N)
    CROSS_FALL_OBJECT,      //!< ������I�u�W�F�N�g(�o�c�}�[�N)
    OGRE_OBJECT,            //!< ����܂��񂪓]�񂾂̋S
    CANNON_OBJECT,          //!< ��C�I�u�W�F�N�g
    DODGEBALL_STAGE_OBJECT, //!< �h�b�W�{�[���V�[���̃X�e�[�W�I�u�W�F�N�g
    DARUMA_FALLDOWN_STAGE_OBJECT, //!< �h�b�W�{�[���V�[���̃X�e�[�W�I�u�W�F�N�g
    SKILL_WALL_OBJECT,      //!< �X�L���ŃX�|�[���ł���ǃI�u�W�F�N�g
    MAX,
};
