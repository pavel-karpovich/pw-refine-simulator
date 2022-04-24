#include <cstring>
#include <random>
#include "Item.hpp"


enum RefineResult
{
    REFINE_SUCCESS			= 0x00,
    REFINE_CAN_NOT_REFINE 	= 0x01,
    REFINE_FAILED_LEVEL_0	= 0x02,	 // мирозданка	//失败，原料消失 装备不变
    REFINE_FAILED_LEVEL_1	= 0x03,	 // подземка	//失败，原料消失 装备降一级
    REFINE_FAILED_LEVEL_2 	= 0x04,	 // небеска	//失败，原料消失 装备归0
};

struct refine_param_t
{
	int need_level;
	float prop[4];	//分别对应 成功 REFINE_FAILED_LEVEL_0 REFINE_FAILED_LEVEL_1 REFINE_FAILED_LEVEL_2
};

static refine_param_t refine_table[]=
{
	{0 ,{ 0.50, 0.7,  0 ,0 }},
	{1 ,{ 0.30, 0,    0 ,1 }},
	{2 ,{ 0.30, 0,    0 ,1 }},
	{3 ,{ 0.30, 0,    0 ,1 }},
	{4 ,{ 0.30, 0,    0 ,1 }},
	{5 ,{ 0.30, 0,    0 ,1 }},
	{6 ,{ 0.30, 0,    0 ,1 }},
	{7 ,{ 0.30, 0,    0 ,1 }},
	{8 ,{ 0.25, 0,    0 ,1 }},
	{9 ,{ 0.20, 0,    0 ,1 }},
	{10,{ 0.12, 0,    0 ,1 }},
	{11,{ 0.05, 0,    0 ,1 }},
};

static float refine_factor[] =
{
	0,	//not use
	1.0f,
	2.0f,
	3.05f,
	4.3f,
	5.75f,
	7.55f,
	9.95f,
	13.f,
	17.05f,
	22.3f,
	29.f,
	37.5f,
};


namespace abase
{
	std::random_device rd;
	std::default_random_engine eng(rd());

	// the real implementation of this module in PW engine is unknown ... unfortunately
	inline float RandomUniform()
	{
		std::uniform_real_distribution<float> distr(0.0, 1.0);
		return distr(eng);
	}
}

int randSelect(const float* option, int size)
{
	float p = abase::RandomUniform();
	for (int i = 0; i < size; i++, option++)
	{
		if (p <= *option)
		{
			return i;
		}
		p -= *option;
	}
	//	ASSERT(p < 1e-6);  // 可能出现 ddr 141226 // может появиться ddr 141226
	return 0;
}

RefineResult refine(EquipementItem* item, RefineEssence* essence)
{
    if (item == nullptr)
    {
        return RefineResult::REFINE_CAN_NOT_REFINE;
    }
	float adjust[4] = {0, 0, 0, 0};
	float adjust2[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (essence != nullptr)
    {
        float adj1 = essence->ext_succeed_prob;
        float adj2 = essence->ext_reserved_prob;
		float adj1 = essence->ext_succeed_prob;
		float adj2 = essence->ext_reserved_prob;

		if (adj1 < 0) adj1 = 0;
		if (adj2 < 0) adj2 = 0;
		if (adj1 > 1.0) adj1 = 1.0;
		if (adj2 > 1.0) adj2 = 1.0;

        adjust[0] = adj1;		// вероятность успеха //成功概率
		adjust[2] = adj2;		// вероятность понижения заточки на 1 //降一级概率
        
		if (essence->fail_reserve_level)
		{
			adjust[1] = 2.0;	// Имеет специальный зарезервированный камень？ //拥有特殊的保留石
		}

		for (size_t i=0; i < 12; i++)
		{
			adjust2[i] = essence->fail_ext_succeed_prob[i];
		}

    }
    size_t addon_level = item->refine_level;
    //超过或者达到最大的级别则不可升级 // Превышение или достижение максимального уровня не может быть улучшено
    if (addon_level >= sizeof(refine_table) / sizeof(refine_param_t))
    {
        return RefineResult::REFINE_CAN_NOT_REFINE;
    }
    
	//考虑概率 // Рассмотрим вероятность
	float prop[4];
	memcpy(prop, refine_table[addon_level].prop, sizeof(prop));

	//对prop进行修正   // внести исправления в реквизит
	prop[0] += adjust[0]; prop[1] += adjust[1];
	prop[2] += adjust[2]; prop[3] += adjust[3];

	if (adjust[1] > 0)
	{
		//若特殊保留概率大于0 则使用adjust2里面带有的成功概率 并忽视原有的成功概率
		// Если специальная вероятность удержания больше 0, используйте вероятность успеха в Adjust2 и игнорируйте исходную вероятность успеха.
		prop[0] = adjust2[addon_level];
	}
	int result = randSelect(prop, 4);

	return (RefineResult)result;
}
