#include "Recognition.h"

    uint8 threshold=0;
//初始化图片

uint8 site[Ra_Max][2] = { 0 };

//辅助部分
void flip(uint8(*image)[COL], uint8(*side_line)[col], uint8* mide_line)
{
	uint8 i, j, k;

	for (i = 1; i < row - 1; i++)
	{
		if (mide_line[i])
			side_line[i][mide_line[i]] = 3;
	}
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			if (side_line[i][j])
				image[i][j] = side_line[i][j];
		}
	for (i = 0; i < row / 2; i++)
		for (j = 0; j < col; j++)
		{
			k = image[i][j];
			image[i][j] = image[row - i - 1][j];
			image[row - i - 1][j] = k;
		}
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			image[ROW - 1 - 2 * i][COL - 1 - 2 * j] = image[row - 1 - i][col - 1 - j];
			image[ROW - 2 - 2 * i][COL - 1 - 2 * j] = image[row - 1 - i][col - 1 - j];
			image[ROW - 1 - 2 * i][COL - 2 - 2 * j] = image[row - 1 - i][col - 1 - j];
			image[ROW - 2 - 2 * i][COL - 2 - 2 * j] = image[row - 1 - i][col - 1 - j];
		}
}
void supplement(uint8(*side_line)[col], uint8 a, uint8 b, uint8 c, uint8 d)
{
	float a1 = a, b1 = b, a2 = c, b2 = d;
	int8 i;
	float s = 0;
	s = ((float)b2 - (float)b1) / ((float)a2 - (float)a1);
	//cout << "b1=" << b << endl;
	if (a1 < a2)
		for (i = a1 + 1; i < a2; i++)
		{
			if ((uint8)(b1 + s * (i - a1)) > 1 && (uint8)(b1 + s * (i - a1)) < col - 2)
				side_line[i][(uint8)(b1 + s * (i - a1))] = 2;
		}
	else
		if (a1 > a2)
			for (i = a2 + 1; i < a1; i++)
			{
				if ((uint8)(b2 + s * (i - a2)) > 1 && (uint8)(b2 + s * (i - a2)) < col - 2)
					side_line[i][(uint8)(b2 + s * (i - a2))] = 2;
			}
		else
			//cout << "ill!" << endl;
	s = ((float)a2 - (float)a1) / ((float)b2 - (float)b1);
	if (b1 < b2)
		for (i = b1 + 1; i < b2; i++)
		{
			if ((uint8)(a1 + s * (i - b1)) > 1 && (uint8)(a1 + s * (i - b1)) < col - 2)
				side_line[(uint8)(a1 + s * (i - b1))][i] = 2;
		}
	else
		if (b1 > b2)
			for (i = b2 + 1; i < b1; i++)
			{
				/*		//cout << "(uint8)(a2 + s * (i - b2))" << (uint8)(a2 + s * (i - b2)) << endl;*/
				if ((uint8)(a2 + s * (i - b2)) > 1 && (uint8)(a2 + s * (i - b2)) < col - 2)
					side_line[(uint8)(a2 + s * (i - b2))][i] = 2;
			}
		else
			////cout << "ill!" << endl;
			;
}
void supplements(uint8(*side_line)[col], uint8 a, uint8 b, uint8 c, uint8 d)
{
    float a1 = a, b1 =col-1-b, a2 = c, b2 = col-1-d;
    int8 i;
    float s = 0;
    s = ((float)b2 - (float)b1) / ((float)a2 - (float)a1);
    //cout << "s=" << s << endl;
    if (a1 < a2)
        for (i = a1 + 1; i < a2; i++)
        {
            if ((uint8)(b1 + s * (i - a1)) > 1 && (uint8)(b1 + s * (i - a1)) < col - 2)
                side_line[i][(uint8)(b1 + s * (i - a1))] = 2;
        }
    else
        if (a1 > a2)
            for (i = a2 + 1; i < a1; i++)
            {
                if ((uint8)(b2 + s * (i - a2)) > 1 && (uint8)(b2 + s * (i - a2)) < col - 2)
                    side_line[i][(uint8)(b2 + s * (i - a2))] = 2;
            }
        else
            s = ((float)a2 - (float)a1) / ((float)b2 - (float)b1);
    s = 1 / s;
    if (b1 < b2)
        for (i = b1 + 1; i < b2; i++)
        {
            if ((uint8)(a1 + s * (i - b1)) > 1 && (uint8)(a1 + s * (i - b1)) < col - 2)
                side_line[(uint8)(a1 + s * (i - b1))][i] = 2;
        }
    else
        if (b1 > b2)
            for (i = b2 + 1; i < b1; i++)
            {
                /*      //cout << "(uint8)(a2 + s * (i - b2))" << (uint8)(a2 + s * (i - b2)) << endl;*/
                if ((uint8)(a2 + s * (i - b2)) > 1 && (uint8)(a2 + s * (i - b2)) < col - 2)
                    side_line[(uint8)(a2 + s * (i - b2))][i] = 2;
            }
}

void supplement_m(uint8(*side_line)[col], uint8* mid_line, uint8 a1, uint8 b1, uint8 a2, uint8 b2)
{
	int8 i;
	float s = 0;
	s = ((float)b2 - (float)b1) / ((float)a2 - (float)a1);
	if (a1 < a2)
		for (i = a1 + 1; i <= a2; i++)						//此处等于的原因是为了更加容易的改变中线最高点，因为最高点一定触边
		{
			side_line[i][(uint8)(b1 + s * (i - a1))] = 2;
			if (side_line[i][(uint8)(b1 + s * (i - a1))] != 2)
			{
				mid_line[i] = (uint8)(b1 + s * (i - a1));
			}
			else
			{
				mid_max = i - 1;
				if (mid_line[i])
					while (mid_line[i])
					{
						mid_line[i] = 0;
						i++;
					}
				break;
			}
		}
	else
		if (a1 > a2)
			for (i = a2 + 1; i <= a1; i++)
			{
				if (side_line[i][(uint8)(b2 + s * (i - a2))] != 2)
				{
					mid_line[i] = (uint8)(b2 + s * (i - a2));
				}
				else
				{
					mid_max = i - 1;
					if (mid_line[i])
						while (mid_line[i])
						{
							mid_line[i] = 0;
							i++;
						}
					break;
				}
			}

}
void point_show(uint8(*side_line)[col], uint8 a, uint8 b)
{
	uint8 i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (a + i > 1 && b + j > 1 && a + i < row + 1 && b + j < col + 1)
				side_line[a + i - 1][b + j - 1] = 5;					//显示金色
			//*//cout << "a=" << a + i - 1 << endl;
			//*//cout << "b=" << b + j - 1 << endl << endl;
		}
	}
}
uint8 line_sway(uint8(*side_line)[col], uint8 a10, uint8 b10, uint8 a20, uint8 b20, uint8 sw)
{
	int16 a1 = a10;
	int16 b1 = b10;
	int16 a2 = a20;
	int16 b2 = b20;
	int16 i, j, k;
	uint8 mark=0;
	float s;
	////cout << endl << "a1=" << a1 << ",a2=" << a2 << ",b1=" << b1 << ",b2=" << b2 << endl;
	s = ((float)a1 - (float)a2) / ((float)b1 - (float)b2);
	////cout << "s=" << abs(s) << endl;
	if (s <= 1 && s > -1)	//上下型遍历
	{
		if (b1 > b2)
		{
			k = b1;
			b1 = b2;
			b2 = k;
			k = a1;
			a1 = a2;
			a2 = a1;
		}
		for (j = b1 + 1; j < b2; j++)
		{
			if(((uint8)(2*(a1 + s * (j - b1))))%2)
				k= a1 + s * (j - b1)+1;
			else
				k= a1 + s * (j - b1);
			////cout << "(uint8(2*(a1 + s * (j - b1))))%2=" << (uint8(2 * (a1 + s * (j - b1)))) % 2 << endl;
			for (i = k- sw; i <= a1 + s * (j - b1) + sw; i++)
			{
				if (i<1 || i>row - 2)
					continue;
				else
				{
					if (side_line[i][j] == 2)
					{
						//side_line[i][j] = 4;
						break;
					}
				}
			}
			if (i == (uint8)(a1 + s * (j - b1) + sw + 1))
				mark++;
		}
	}
	else
	{
		s = 1 / s;
		if (a1 > a2)
		{
			k = b1;
			b1 = b2;
			b2 = k;
			k = a1;
			a1 = a2;
			a2 = a1;
		}
		////cout << "反侧" << endl;
		for (i = a1 + 1; i < a2; i++)
		{
			////cout << "(uint8(2 * (b1 + s * (i - a1)))) % 2=" << (uint8(2 * (b1 + s * (i - a1)))) % 2 << endl;
			if (((uint8)(2 * (b1 + s * (i - a1)))) % 2)
				k = b1 + s * (i - a1) + 1;
			else
				k = b1 + s * (i - a1);
			for (j = k - sw; j <= b1 + s * (i - a1) + sw; j++)
			{
				if (j<1 || j>col - 2)
					continue;
				else
				{
					if (side_line[i][j] == 2)
					{
						//side_line[i][j] = 3;
						break;
					}
				}
			}
			if (j == (uint8)(b1 + s * (i - a1) + sw + 1))
				mark++;
		}
	}
	return mark;
}


//八邻域部分
uint8 nighbor_judge(uint8(*p)[COL], uint8(*line)[col], uint8 a, uint8 b, uint8 n)//邻域判定
{
	if (p[a][b])
		return 0;
	uint8 i, j;
	uint16 k = 0, c = 0;
	//横向扫描
	do {
		for (i = 0; i < 3; i += 2)
		{
			for (j = 0; j < 2; j++)
			{
				////cout << b - 1 + j << endl;
				if (line[a - 1 + i][b - 1 + j] == n)
					continue;
				if (line[a - 1 + i][b + j] == n)
					break;
				if (p[a - 1 + i][b - 1 + j] != p[a - 1 + i][b + j])
					if (!p[a - 1 + i][b - 1 + j] && line[a - 1 + i][b - 1 + j] != n)
					{
						line[a - 1 + i][b - 1 + j] = n;
						site[k][0] = a - 1 + i;
						site[k++][1] = b - 1 + j;
					}
					else
						if (!p[a - 1 + i][b + j] && line[a - 1 + i][b + j] != n)
						{
							line[a - 1 + i][b + j] = n;
							site[k][0] = a - 1 + i;
							site[k++][1] = b + j;
						}
			}
		}
		for (j = 0; j < 3; j += 2)
		{
			for (i = 0; i < 2; i++)
			{
				if (line[a - 1 + i][b - 1 + j] == n)
					continue;
				if (line[a + i][b - 1 + j] == n)
					break;
				if (p[a - 1 + i][b - 1 + j] != p[a + i][b - 1 + j])
					if (!p[a - 1 + i][b - 1 + j] && line[a - 1 + i][b - 1 + j] != n)
					{
						line[a - 1 + i][b - 1 + j] = n;
						site[k][0] = a - 1 + i;
						site[k++][1] = b - 1 + j;
					}
					else
						if (!p[a + i][b - 1 + j] && line[a + i][b - 1 + j] != n)
						{
							line[a + i][b - 1 + j] = n;
							site[k][0] = a + i;
							site[k++][1] = b - 1 + j;
						}
			}
		}
		if (k > Ra_Max - 9)
			return 0;
		site[c][0] = 0;
		site[c++][1] = 0;
		a = site[c][0];
		b = site[c][1];
	} while (a);
	return k;
}


//中线探寻

void mid_seek(uint8(*side_line)[col], uint8* mid_line, uint8* r_line, uint8* l_line)
{
	uint8 i, j;
	//初始化
	if (!mid_line[1])
	{
		for (l_line[1] = 1; side_line[1][l_line[1]] != 2; l_line[1]++);
		for (r_line[1] = col - 2; side_line[1][r_line[1]] != 2; r_line[1]--);
		mid_line[1] = (l_line[1] + r_line[1]) / 2;
	}
	//探寻中线，得出mid_max

	for (i = 2; i < row - 2; i++)
	{
		if (side_line[i][mid_line[i - 1]] == 2)
		{
			mid_line[i] = mid_line[i - 1];			//此处使得边点与中线触及；
			break;
		}
		for (j = mid_line[i - 1]; j < col - 1; j++)
			if (side_line[i][j] == 2)
			{
				r_line[i] = j;
				break;
			}
		for (j = mid_line[i - 1]; j; j--)
			if (side_line[i][j] == 2)
			{
				l_line[i] = j;
				break;
			}
		mid_line[i] = (r_line[i] + l_line[i]) / 2;
	}
	mid_max = i - 1;

	//cout << "mid_max=" << mid_max << endl;

	//此处进行异常触变问题的解决，在给出的中线最大高度与边线最大高度距离过大时，进行考虑

	if (mid_max + Mid_Side_DM < side_max)
	{
		//算法一：底边边点中点与最高点边点中点进行补线，以此计算中线，并进行处理

		////cout << "side_max" << side_max << endl;
		//point_show(side_max, 20, side_line);
		if (side_max >= row - 15)		//要求变线最高点在最高点
		{
			//cout << "进行中线补线！" << endl;
			uint8 l_point = 1, r_point = col - 2;
			for (j = 1; j < col - 2; j++)
			{
				if (side_line[side_max][j] == 2)
				{
					l_point = j;
					j = col - 1;
					while (side_line[side_max][--j] != 2 && j);
					r_point = j - 1;
					break;
				}
			}
			//中线补线
			mid_max = side_max;
			supplement_m(side_line, mid_line, side_max - 1, (r_point + l_point) / 2, 2, mid_line[2]);
		}
		//cout << "judge:" << mid_max + Mid_Side_DM << ">=" << side_max << endl;
		if (mid_max + Mid_Side_DM >= side_max)
		{

			for (i = 2; i < mid_max; i++)
			{
				for (j = mid_line[i]; j < col - 1; j++)
					if (side_line[i][j] == 2)
					{
						r_line[i] = j;
						break;
					}
				for (j = col / 2; j > 1; j--)
					if (side_line[i][j] == 2)
					{
						l_line[i] = j;
						break;
					}
				////cout << "i=" << i << endl;
				////cout << "r_line:" << r_line[i] << ",l_line:" << l_line[i] << endl;
			}
		}
		////cout << "mid_max1=" << mid_max << endl;
		//算法二：对前序正常中线进行拟合，最终处理得到后续中线

		//if (mid_max + Mid_Side_DM < side_max || side_max != row - 2) {；//未编写，在算法一未执行与未成功的情况下进行处理}
	}

}
void mid_seeks(uint8(*side_line)[col], uint8* mid_line)
{
	uint8 i, j;
	uint8 r = 0, le = 0;
	//写入
	for (i = 2; i < row - 2; i++)
	{
		if (side_line[i][mid_line[i - 1]] == 2)
		{
			mid_line[i] = mid_line[i - 1];			//此处使得边点与中线触及；
			break;
		}
		for (j = mid_line[i - 1]; j < col - 1; j++)
			if (side_line[i][j] == 2)
			{
				r = j;
				break;
			}
		for (j = mid_line[i - 1]; j; j--)
			if (side_line[i][j] == 2)
			{
				le = j;
				break;
			}
		mid_line[i] = (r + le) / 2;
	}
	//归零
	for (; i < row - 2; i++)
	{
		if (mid_line[i])
			mid_line[i] = 0;
	}
	mid_max = i;
}

//寻线

void binarization(uint8(*p)[COL])
{
	int i, j, nm;
	uint16  g[256] = { 0 };
	float n;
	float sum = 0;				//灰度总值
	float sums = 0;
	uint16 num = 0;				//所含数据最大量
	uint16 nums = 0;
	uint16 Grey_max, Grey_min;
	uint8 c = col, r = row;
	num = (c - 4-(c-4)/2) * (r - 4-(r-4)/2);
	for (i = 2; i < row - 2; i +=2)
		for (j = 2; j < col - 2; j +=2)
		{
			g[p[2 * i][2 * j]]++;
			sum += p[2 * i][2 * j];
		}
	//计算最小灰度值
	for (Grey_min = 0; !g[Grey_min]; Grey_min++);

	//计算最大灰度值
	for (Grey_max = 255; !g[Grey_max]; Grey_max--);

//	          ips114_showstr(0,5,"Grey_max");
//	          ips114_showint16(8*13,5,Grey_max);
//	           ips114_showstr(0,6,"Grey_min");
//	          ips114_showint16(8*13,6,Grey_min);

	if(Grey_min+70<Grey_max)
	{

	sums = g[Grey_min] * Grey_min;
	nums = g[Grey_min];

	for (i = Grey_min + 1, threshold = Grey_min, nm = 0; i < Grey_max; i++)
	{
		sums += g[i] * i;
		nums += g[i];

		n = sums / nums * sums + (sum - sums) / (num - nums) * (sum - sums);

		if (n > nm)
		{
			threshold = i;
			nm = n;
		}
	}
    }
	else {
        return;
    }
	//cout << "threshold=" << threshold << endl;
	//最高-最低范围测试

	//二值化
	for (j = 2; j < col - 2; j++)
		for (i = 2; i < row - 2; i++)
		{
			if (p[ROW - 1 - 2 * i][2 * j] < threshold)
			{
				p[i][j] = 0;
			}
			else
			{
				p[i][j] = 1;
			}
		}

	//增加边框
	for (i = 0; i < row; i++)
	{
		p[i][0] = 0;
		p[i][1] = 0;
		p[i][col - 1] = 0;
		p[i][col - 2] = 0;
	}
	for (j = 2; j < col - 2; j++)
	{
		p[0][j] = 0;
		p[1][j] = 0;
		p[row - 1][j] = 0;
		p[row - 2][j] = 0;
	}

}
uint8 line_hunting(uint8(*p)[COL], uint8(*side_line)[col])//八邻域法
{
	//由于判断标准为二行为白点，返回为一行中点，即在寻中时不会出现二行触边情况，即不予考虑实际中点

	uint8 j;
	uint16 ra = 0;



	if (p[2][col / 2])
	{
		ra = nighbor_judge(p, side_line, 1, col / 2, 2);
		//cout << "ra=" << ra << endl;
		if (ra == 0)
		{
			//边点过载
			if (side_line[1][col / 2] == 2)
				return 0;
		}
		else						//一切正常，进行边点值搜寻
		{
			return col / 2;
		}
	}
	//非正常中点

	for (j = 2; j < col - 2; j++)
	{
		////cout << p[2][j] << " ";
		if (p[2][j])
		{
		ra = nighbor_judge(p, side_line, 1, j, 2);
		//cout << "ra=" << ra << endl;
		if (!ra)
			continue;
		else
			return 1;
		}
	}

	return  0;

}
uint8 destination(uint8(*side_line)[col], uint8(*p)[COL],uint8 A)
{
    if(side_max)
    if(side_max<=A+3)
        return 0;
	uint8 i;
	uint8 lock = 0;
	uint8 mark = 0;
	for (i = 2; i <= A; i++)
	{
		if (side_line[i][col / 2] == 2)
		{
			return 0;
		}
	}
	for (i = col / 2; i && side_line[A][i] != 2; i--)
	{

		if (p[A][i] == 0 && lock == 0)
		{
			lock = 1;
			mark++;
		}
		if (lock && p[A][i])
		{
			lock = 0;
		}
	}

	for (i = col / 2, lock = 0; i < col - 1 && side_line[A][i] != 2; i++)
	{
		if (p[A][i] == 0 && lock == 0)
		{
			lock = 1;
			mark++;
		}
		if (lock && p[A][i])
		{
			lock = 0;
		}
	}

	if (mark >= D_mark - 1)			//减一目的为消除存在的两次判定
		return 1;

	//边线部分

	mark = 0;

	for (i = col / 2, lock = 0; i; i--)
	{

		if (side_line[A][i] == 2 && lock == 0)
		{
			lock = 1;
			mark++;
		}
		if (lock && side_line[A][i] == 0)
		{
			lock = 0;
		}
	}

	for (i = col / 2,lock = 0; i < col - 1; i++)
	{
		if (side_line[A][i] == 2 && lock == 0)
		{
			lock = 1;
			mark++;
		}
		if (lock && side_line[A][i] == 0)
		{
			lock = 0;
		}
	}

	//cout << "mark2=" << mark << endl;
	if (mark >= D_mark - 1)			//减一目的为消除存在的两次判定
		return 1;
	else
		return 0;
}

//偏移量处理

int8 mid_value(uint8* mid_line, uint8(*side_line)[col])
{
	uint8 i, j;
	uint8 max;
	float m;
	uint16 d;
	uint8 right[row] = { 0 }, left[row] = { 0 };	//防止图片初始影响，后续可改换
//	if (A_max < right_b || A_max < left_b)
//	{
//		return 0;
//	}

	if(mid_max)
		max =mid_max-1;
	else {
        return 0;
    }
		for (i = 2, d = 0, m = 0; i < max; i++)
		{
			for (j = mid_line[i]; j < col - 1; j++)
				if (side_line[i][j] == 2)
					right[i] = j;
			for (j = mid_line[i]; j; j--)
			{
				if (side_line[i][j] == 2)
					left[i] = j;
			}
			d += (right[i] - left[i]);
			m += mid_line[i] * (right[i] - left[i]);
		}
//	    ips114_showstr(0,5,"m");
//	              ips114_showint16(8*13,5,m);
//	               ips114_showstr(0,6,"d");
//	              ips114_showint16(8*13,6,d);
		m /= d;
		m -= col / 2;
//	    ips114_showstr(0,7,"ang");
//	              ips114_showint16(8*13,7,m);

	angular_c = m;
	return 1;
}

