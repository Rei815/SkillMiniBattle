#pragma once

 /*!
  *  @brief      �G�t�F�N�gID
  */
enum class EFFECT_ID
{
    DESTROY,                //!< ���j�G�t�F�N�g
    HIT,                    //!< �q�b�g�G�t�F�N�g
    HIT_INVINCBLE,          //!< �q�b�g�G�t�F�N�g(���G��)
    DAMAGE,                 //!< �_���[�W�G�t�F�N�g
    JUMP,                   //!< �W�����v�G�t�F�N�g
    DUST_CLOUD,             //!< �y���G�t�F�N�g
    EMERGENCY,              //!< �x���G�t�F�N�g
    SHOCK_WAVE,             //!< �Ռ��g�G�t�F�N�g
    PLAYER_BULLET,          //!< �v���C���[�e�G�t�F�N�g
    ENEMY_BULLET,           //!< �G�l�~�[�e�G�t�F�N�g
    FORECAST_LINE,          //!< ��C�̖C���\����
    SKILL_BARRIER,          //!< �X�L���ɂ��o���A�G�t�F�N�g
    FLOATING,               //!< ���V�G�t�F�N�g
    GRAVITY_AREA,           //!< �d�̓G���A�G�t�F�N�g
    STRONG_WIND,            //!< �����G�t�F�N�g
    COLLIDE,                //!< �Ԃ��������̃G�t�F�N�g
    SKILL_STAR,             //!< �X�L���������̋��ʃG�t�F�N�g
    OGRE_CONTROL,           //!< �S����̃G�t�F�N�g
    DEBUFF,                 //!< �f�o�t�G�t�F�N�g
};
