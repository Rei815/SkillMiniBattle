#include "dust_cloud_effect.h"

const std::string CDustCloudEffect::m_file_name = "data\\Effects\\dust_cloud_effect.efk";

CDustCloudEffect::CDustCloudEffect()
	: IEffect(m_file_name, EFFECT_ID::DUST_CLOUD)
{
}

CDustCloudEffect::~CDustCloudEffect()
{
}
