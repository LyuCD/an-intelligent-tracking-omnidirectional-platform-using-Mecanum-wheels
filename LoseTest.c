#include "Recognition.h"

int8 lose_test(uint8(*side_line)[col])
{
	//cout << endl << "丢失测试：" << endl;
	int8 i, j;
	uint8 lock;
	uint8 rmax, lmax;
	uint8 right = 0, left = 0;		//边线锁，边线最大值可用条件
	int16 k;
	//入环预判

	if (round_in || round_out)
		if (Round_D == -1)
		{
			uint8 lh = 0;
			uint8 rh = 0;
			uint8 ll = 0;
			uint8 rl = 0;
			uint8 use = 0;
			for (lh = 2; side_line[row - 2][lh] == 2; lh++);

			for (i = row - 3; i > 1; i--)
			{
				if (side_line[i][1] != 2)
				{
					use = 1;
					break;
				}
			}
			//ips114_showstr(0, 5, "use");
			//ips114_showint16(8 * 13, 5, use);
			if (!use)
			{
				for (rh = col - 2; side_line[row - 2][rh] != 2; rh--);

				//        ips114_showstr(0,5,"lh");
				//        ips114_showint16(8*13,5,lh);
				//                   ips114_showstr(0,6,"rh");
				//                  ips114_showint16(8*13,6,rh);
				if (rh + 1 == lh)
				{
					for (ll = 2; side_line[1][ll] == 2; ll++);
					for (rl = col - 2; side_line[1][rl] != 2; rl--);
					//ips114_showstr(0, 5, "rl");
					//ips114_showint16(8 * 13, 5, rl);
					//ips114_showstr(0, 6, "ll");
					//ips114_showint16(8 * 13, 6, ll);
					if (rl + 1 == ll && rh < rl)
					{

						//ips114_showstr(0, 7, "lh");
						//ips114_showint16(8 * 13, 7, lh);

						if (lh<Rh_max && lh>Rh_min)
						{
							if (round_out)
							{
								angular_c = Round_out_angular;
							}
							else {
								angular_c = Round_angular_s;
							}
							return 6;
						}
					}
				}
			}
		}
		else
		{
			uint8 lh = 0;
			uint8 rh = 0;
			uint8 ll = 0;
			uint8 rl = 0;
			uint8 use = 0;
			for (rh = col - 3; side_line[row - 2][rh] == 2; rh--);

			for (i = row - 3; i > 1; i--)
			{
				if (side_line[i][col-2] != 2)
				{
					use = 1;
					break;
				}
			}
			if (!use)
			{
				for (lh = 1; side_line[row - 2][lh] != 2; lh++);

				if (rh + 1 == lh)
				{
					for (ll = 1; side_line[1][ll] != 2; ll++);
					for (rl = col - 3; side_line[1][rl] == 2; rl--);
					if (rl + 1 == ll && lh > ll)
					{
						if (col-1-lh<Rh_max && col-1-lh>Rh_min)
						{
							if (round_out)
							{
								angular_c = Round_out_angular;
							}
							else {
								angular_c = Round_angular_s;
							}
							return 6;
						}
					}
				}
			}
		}

	//round_out=1;
	//初始化边点特征值
	{
		for (i = row - 2; i > 0; i--)
		{
			for (j = 1; j < col - 1; j++)
				if (side_line[i][j] == 2)
					break;
			if (j != col - 1)
				break;
		}
		side_max = i;
		for (i = side_max; i && side_line[i][1] != 2; i--);
		left_b = i;
		for (i = side_max; i && side_line[i][col - 2] != 2; i--);
		right_b = i;
		////cout << "side_max=" << side_max << endl;
		////cout << "left_b=" << left_b << endl;
		////cout << "right_b=" << right_b << endl;
	}

	//寻找左最大边点与边线丢失可信点

	//左侧部分
	for (i = side_max; i > 1; i--)
	{
		if (side_line[i][1] == 2)
			break;
	}

	////cout << "i=" << i << endl;

	//测试存在角未识别错误，并修复
	lmax = left_b;
	if (side_line[lmax + 1][2] == 2 && side_line[i + 1][3] == 2)
		i++;
	lmax = i;
	////cout << " side_line[i+1][2]=" << side_line[i + 1][2] << endl;

	//测试锁，达到下寻全丢失时打开
	k = 0;
	i--;
	while (i > 1)
	{
		if (side_line[i + 1][1] != 2)
		{

			k++;
		}
		i--;
	}
	//cout << "k1=" << k << endl;
	if (k < Lose_k)						//小于限制时视为出现
		left = 1;

	//右侧部分

	for (i = side_max; i; i--)
	{
		if (side_line[i][col - 2] == 2)
			break;
	}


	if (side_line[i + 1][col - 3] == 2 && side_line[i + 1][col - 4] == 2)
		i++;
	rmax = i;
	k = 0;
	i--;
	while (i > 1)
	{
		if (side_line[i][col - 2] != 2)
			k++;
		i--;
	}
	//cout << "k2=" << k << endl;
	if (k < Lose_k)
		right = 1;

	//cout << "rmax=" << rmax << " lmax=" << lmax << endl;
	//cout << "right=" << right << " left=" << left << endl;


	if (right && left && rmax > row - 3 && lmax > row - 3)//lmax与rmax均刚好达到最高点
	{
		float a1 = 0, a2 = 0;
		float min[2] = { 0 };
		uint8 point[2] = { 0 };
		//左侧部分
		for (j = 2; side_line[row - 3][j] != 2 && j < col - 2; j++);
		min[0] = row - 3;
		min[1] = j;
		//point_show(side_line, min[0], min[1]);
		for (i = row - 4; i > 1; i--)
		{
			for (j = 2; side_line[i][j] != 2 && j < col - 2; j++);
			if (j <= min[1])
			{
				min[1] = j;
				min[0] = i;
			}
			if (j == col - 2)
				break;
		}
		i++;
		for (j = 2; side_line[i][j] != 2 && j < col - 2; j++);
		point[0] = i;
		point[1] = j;

		if (round_out)
		{
			if (Round_D == -1)
			{
				if (point[0] < row - 3)
				{
					supplement(side_line, 1, 1, point[0], point[1]);
					uint8 mid_line[row] = { col / 2,col / 2 };
					mid_seeks(side_line, mid_line);
					mid_value(mid_line, side_line);
					return 1;
				}
				else {
					return 9;
				}
			}
			else
			{
				supplement(side_line, 1, col-1, point[0], point[1]);
				uint8 mid_line[row] = { col / 2,col / 2 };
				mid_seeks(side_line, mid_line);
				mid_value(mid_line, side_line);
				return 1;

			}
		}
		a1 = -atan((min[0] - point[0]) / (min[1] - point[1])) * 180 / PI;
		////cout << "a1=" << a1 << endl;
		//右侧部分
		for (j = col - 3; side_line[row - 3][j] != 2 && j > 1; j--);
		min[0] = row - 3;
		min[1] = j;
		point_show(side_line, min[0], min[1]);
		for (i = row - 4; i > 1; i--)
		{
			for (j = col - 3; side_line[i][j] != 2 && j > 1; j--);
			if (j >= min[1])
			{
				min[1] = j;
				min[0] = i;
			}
			if (j == 1)
				break;
		}
		i++;
		for (j = col - 3; side_line[i][j] != 2 && j < col - 2; j--);
		point[0] = i;
		point[1] = j;
		a2 = atan((min[0] - point[0]) / (min[1] - point[1])) * 180 / PI;

		if (!round_in && !round_out)
		{
			if (180 - a1 - a2< TriA_max && 180 - a1 - a2 >TriA_min)
			{
				return 4;
			}
			else
				return 1;
		}
	}

	//出环丢失测试
	if (round_out || sta_begain_delay)
		if (rmax < row - 1 - High_b && lmax < row - 1 - High_b && lmax > High_Sway && rmax > High_Sway)		//未完全开锁且未达到顶点,并保证最低有效
			if (rmax + Side_Sway >= side_max || lmax + Side_Sway >= side_max)	//一边达到最高点
			{
				//cout << "出环测试：" << endl;
				float k;
				uint8 n = 0;
				k = ((float)rmax - (float)lmax) / ((float)col - 2);
				//进行摇摆宽度判断
				for (j = 1; j < col - 2; j++)
				{
					lock = 0;
					for (i = lmax - High_Sway + k * (j - 1); i <= lmax + High_Sway + k * (j - 1) && i < row - 1; i++)
					{
						if (side_line[i][j] == 2)
						{
							lock = 1;
							break;
						}
					}
					if (lock == 0)
					{
						if (n < 250)
							n++;
						else
							break;
					}
				}
				//	           ips114_showstr(0,3,"high_n");
				//	           ips114_showint16(8*13,3,n);

				if (n < High_n)
				{
					//cout << "出环！" << endl;
					if (sta_begain_delay)
					{
						angular_c = Begain_angular;
					}
					else
						angular_c = Round_angular;						//输出最大左转偏移
					return 5;
				}
			}

	//判断左右丢失

	if (right && left && (rmax + 2 * Side_Sway >= side_max || lmax + 2 * Side_Sway >= side_max))						//在左右均可用的情况下			
	{

		//判断三岔口与入环丢失
		float m = 0;
		int d;
		lock = 0;


		//cout << "判断三岔口与入环丢失:" << endl;
		//角点判断
		if (lmax > 2 && rmax > 2)
		{
			float a1 = 0, a2 = 0;
			for (j = 0; side_line[lmax - 1][j + 2] != 2 && j < col - 3; j++);
			d = j;
			for (i = lmax - 2; i > 1; i--)				//减一的目的为消除出环问题
			{
				for (j = 0; side_line[i][j + 2] != 2 && j < col - 3; j++);
				if (j > d + RLS && j + 2 >= col - 3)
				{
					i++;
					lock = 1;
					//cout << i << "/" << row - 1 << "处出现判断角点！" << endl;
					break;
				}
				else
				{
					m += j;
					d = j;
				}
			}
			//判断出现角点
			if (m > 10 && d > 5 && lock)
			{

				a1 = atan(2 * (float)m / ((float)d) / ((float)d)) * 180 / PI;

				//右侧部分；

				m = 0;
				for (j = 0; side_line[i][col - 3 - j] != 2 && j < col - 3; j++);
				d = j;
				for (i++; i < rmax; i++)
				{
					for (j = 0; side_line[i][col - 3 - j] != 2 && j < col - 3; j++);
					if (!j)
						break;
					else
					{
						m += j;
					}
				}
				//cout << "m=" << m << ",d=" << d << endl;
				if (m > 10)
					a2 = atan(2 * (float)m / ((float)d) / ((float)d)) * 180 / PI;

				//cout << "a1=" << a1 << ",a2=" << a2 << endl;
				//cout << "判断角度：" << 180 - a1 - a2 << endl;

				//三岔口判定
				if (!round_in && !round_out)
				{

					if (180 - a1 - a2< TriA_max && 180 - a1 - a2 >TriA_min)
					{
						//cout << "出现三岔口！" << endl;
						//右转
						return 4;
					}
				}
				//出环判定
				if (round_in || round_out)
					if ((180 - a1 - a2< Round_A_max && 180 - a1 - a2 >Round_A_min) || (!(lmax + Side_Sway >= side_max && rmax < row - 2 - Lose_dec) && !(rmax + Side_Sway >= side_max && lmax < row - 2 - Lose_dec)))
					{
						//cout << "出现环岛入环！" << endl;
						//cout << "D=" << D << endl;

						if (round_out == 0)
						{
							angular_c = Round_in_angular;
							round_out_delay = Round_out_use_delay;
						}
						else
							angular_c = Round_out_angular;
						return 5;
					}
			}
		}

		//左右丢失测试

		{
			//右侧丢失
			if (rmax + Side_Sway >= side_max && lmax < row - 2 - Lose_dec)				//在距离一定的边线最高点范围内
			{
				k = 0;
				//此处进行扫描
				if (lmax)
					for (i = lmax - 1; i > 1; i--)
					{
						for (j = 2; j < col - 2; j++)
						{
							if (side_line[i][j] == 2)
								k++;
						}
					}
				//cout << "k0=" << k << endl;
				if (k < 4)			//此处考虑四个点内可以认定丢失
				{
					if (lmax == 0)
						lmax = 1;
					//for (k = 1; side_line[lmax][k] != 2; k++);
					//for (i = col - 3; side_line[rmax][i] == 2; i--);
					//i++;
					if (rmax <= lmax)
						return 0;
					//supplement(side_line, lmax, k, rmax, i);
					//angular_c = prespective(side_line, lmax, k, rmax, i) * ES;
					for (i = rmax - 1, m = 0, d = 0; i > lmax; i--)
					{
						for (j = col - 3; side_line[i][j] != 2 && j; j--);
						d += (col - 2 - j);
						m += (col - 2 - j) * (col - 2 - j) / 2;
					}
					m /= d;
					m = col / 2 - m;
					//cout << "右侧丢失" << "m=" << m << endl;
					angular_c = m;
					return 2;
				}
			}

			//左侧丢失
			if (lmax + Side_Sway >= side_max && rmax < row - 2 - Lose_dec)
			{
				k = 0;
				if (rmax)
					for (i = rmax - 1; i > 1; i--)
					{
						for (j = 2; j < col - 2; j++)
						{
							////cout << "side_line[" << i << "][" << j << "]=" << side_line[i][j] << endl;
							if (side_line[i][j] == 2)
								k++;
						}
					}
				//cout << "k=" << k << endl;
				if (k < 4)
				{
					if (rmax == 0)
						rmax = 1;
					//for (i = col - 2; side_line[rmax][i] != 2; i--);
					//for (k = 2; side_line[lmax][k] == 2; k++);
					//k--;
					if (rmax >= lmax)
						return 0;
					////cout << " lmax, k, rmax, i=" << lmax << "," << k << "," << rmax << "," << i << endl;

					for (i = lmax - 1, m = 0, d = 0; i > rmax && i < col - 2; i--)
					{
						for (j = 2; side_line[i][j] != 2; j++);
						d += (j - 1);
						m += (j - 1) * (j - 1) / 2;
					}
					//cout << "m=" << m << endl;
					//cout << "d=" << d << endl;
					m /= d;
					m -= col / 2;
					//cout << "左侧丢失" << "m=" << m << endl;
					angular_c = m;
					return 80;
				}
			}
		}

	}
	//未寻到任何丢失
	//cout << "未寻得任何丢失元素！" << endl;
	return 0;
}
