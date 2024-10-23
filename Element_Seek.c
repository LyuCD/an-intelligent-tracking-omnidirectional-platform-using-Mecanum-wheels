
#include "Recognition.h"

uint8 element_seeks(uint8(*side_line)[col], uint8(*p)[COL], uint8* mid_line)
{
	uint8 i, j;
	uint8 mark;
	uint8 right[row] = { 0 };
	uint8 left[row] = { 0 };

	uint8 r_out = 0;
	uint8 r_in = 0;
	uint8 l_out = 0;
	uint8 l_in = 0;


	//过环封闭

    if(sta_mark_delay>0&&sta_in_lock==0)
    {
        mid_seek(side_line, mid_line, (uint8*)right, (uint8*)left);

        //跳变检测

        for (i = 2; i + 1 < mid_max; i++)
        {
            if (!r_out && right[i] + RLS < right[i + 1])
            {
                r_out = i;
            }
            if (right[i] > right[i + 1] + RLS)
            {
                r_in = i + 1;
            }
            if (!l_out && left[i] > left[i + 1] + RLS)
            {
                l_out = i;
            }
            if (left[i] + RLS < left[i + 1])
            {
                l_in = i + 1;
            }
        }
        if(l_in)
        {
            supplement(side_line, l_in, left[l_in], 1, 1);
        }
        if(r_in)
        {
            supplement(side_line, r_in, right[r_in], 1, col-2);
        }
        mid_seeks(side_line, mid_line);
        mid_value(mid_line, side_line);
        return 6;
    }


	if (Round_D == -1)
	{
		mid_seek(side_line, mid_line, (uint8*)right, (uint8*)left);

		//跳变检测

		for (i = 2; i + 1 < mid_max; i++)
		{
			if (!r_out && right[i] + RLS < right[i + 1])
			{
				r_out = i;
			}
			if (right[i] > right[i + 1] + RLS)
			{
				r_in = i + 1;
			}
			if (!l_out && left[i] > left[i + 1] + RLS)
			{
				l_out = i;
			}
			if (left[i] + RLS < left[i + 1])
			{
				l_in = i + 1;
			}
		}
		//cout << "l_in=" << l_in << ",l_out=" << l_out << ",r_in=" << r_in << ",r_out=" << r_out << endl;
		if (round_out || (round_in_delay && !round_in))
		{
			supplement(side_line, mid_max - 1, left[mid_max - 1], 2, left[2]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 4;
		}

		//入环阶段
		if (round_in)
		{
			if (!r_in && !r_out)
			{
				if (l_in)
				{
					//出现跳变，入环
					supplement(side_line, l_in, left[l_in], 2, right[2]);
					mid_seeks(side_line, mid_line);
					mid_value(mid_line, side_line);
					round_out_delay = Round_out_use_delay;
					return 1;
				}
				else
				{
					//未出现，继续
					supplement(side_line, mid_max - 1, left[mid_max - 1], 2, left[2]);
					mid_seeks(side_line, mid_line);
					mid_value(mid_line, side_line);
					return 4;
				}
			}
			else
			{
				if (r_out)
				{
					supplement(side_line, mid_max - 1, right[mid_max - 1], r_out, right[r_out]);
				}
				if (r_in)
				{
					supplement(side_line, 1, col - 2, r_out, right[r_out]);
				}
				mid_seeks(side_line, mid_line);
				mid_value(mid_line, side_line);
				return 4;
			}
			return 6;
		}

		//十字部分

		if (r_in && l_in && !r_out && !l_out)	//仅内跳
		{
			supplement(side_line, r_in, right[r_in], 2, right[2]);
			supplement(side_line, l_in, left[l_in], 2, left[2]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 3;
		}
		if (r_out && l_out && !r_in && !l_in)	//仅外跳
		{
			if (r_out > 3 && l_out > 3)
			{
				//此处将下线拟合补充上线
				float a;
				a = ((float)right[r_out] - right[2]) / ((float)r_out - 2.0);
				if ((int)right[r_out] + a * (row - 2 - r_out) > col - 2 || (int)right[r_out] + a * (row - 2 - r_out) < 1)
					r_in = col - 2;
				else
					r_in = right[r_out] + a * (row - 2 - r_out);
				a = ((float)left[l_out] - left[2]) / ((float)l_out - 2.0);
				if ((int)left[l_out] + a * (row - 2 - l_out) > col - 2 || (int)left[l_out] + a * (row - 2 - l_out) < 1)
					l_in = 1;
				else
					l_in = left[l_out] + a * (row - 2 - l_out);
				supplement(side_line, row - 2, r_in, r_out, right[r_out]);
				supplement(side_line, row - 2, l_in, l_out, left[l_out]);
				mid_seeks(side_line, mid_line);
				mid_value(mid_line, side_line);
				return 3;
			}
			else
				return 7;
		}
		if (r_in && r_out && l_in && l_out)			//全十字
		{
			supplement(side_line, r_in, right[r_in], r_out, right[r_out]);
			supplement(side_line, l_in, left[l_in], l_out, left[l_out]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 3;
		}

		//过环判断位

		if (l_out && !r_out && !r_in)
		{
			//cout << "过环判断位" << endl;

			for (i = left[l_out + 1] + 1, mark = 0; i < left[l_out]; i++)
			{
				for (j = 0; l_out - j && side_line[l_out - j][i] != 2; j++);
				mark += j;
			}
			if (mark >= Round_pass)
			{
				//触发为入环延迟，延迟结束后触发入环
				round_in_delay = Round_in_unuse_delay;
			}

			//        ips114_showstr(0,5,"round_mark");
			//         ips114_showint16(8*13,5,mark);
			supplement(side_line, l_out, left[l_out], mid_max, left[mid_max]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 2;
		}
	}
	else
	{
		mid_seek(side_line, mid_line, (uint8*)left, (uint8*)right);

		for (i = 1; mid_line[i]; i++)
		{
			left[i] = col - 1 - left[i];
			right[i] = col - 1 - right[i];
		}


		//跳变检测
		for (i = 2; i + 1 < mid_max; i++)
		{

			if (!r_out && right[i] + RLS < right[i + 1])
			{
				r_out = i;
			}
			if (right[i] > right[i + 1] + RLS)
			{
				r_in = i + 1;
			}
			if (!l_out && left[i] > left[i + 1] + RLS)
			{
				l_out = i;
			}
			if (left[i] + RLS < left[i + 1])
			{
				l_in = i + 1;
			}
		}
		//cout << "l_in=" << l_in << ",l_out=" << l_out << ",r_in=" << r_in << ",r_out=" << r_out << endl;
		if (round_out || (round_in_delay && !round_in))
		{
			supplements(side_line, mid_max - 1, left[mid_max - 1], 2, left[2]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 4;
		}

		//入环阶段
		if (round_in)
		{
			if (!r_in && !r_out)
			{
				if (l_in)
				{
					//出现跳变，入环
					supplements(side_line, l_in, left[l_in], 2, right[2]);
					mid_seeks(side_line, mid_line);
					mid_value(mid_line, side_line);
					round_out_delay = Round_out_use_delay;
					return 1;
				}
				else
				{
					//未出现，继续
					supplements(side_line, mid_max - 1, left[mid_max - 1], 2, left[2]);
					mid_seeks(side_line, mid_line);
					mid_value(mid_line, side_line);
					return 4;
				}
			}
			else
			{
				if (r_out)
				{
					supplements(side_line, mid_max - 1, right[mid_max - 1], r_out, right[r_out]);
				}
				if (r_in)
				{
					supplements(side_line, 1, col - 2, r_out, right[r_out]);
				}
				mid_seeks(side_line, mid_line);
				mid_value(mid_line, side_line);
				return 4;
			}
			return 6;
		}

		//十字部分

		if (r_in && l_in && !r_out && !l_out)	//仅内跳
		{
			supplements(side_line, r_in, right[r_in], 2, right[2]);
			supplements(side_line, l_in, left[l_in], 2, left[2]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 3;
		}
		if (r_out && l_out && !r_in && !l_in)	//仅外跳
		{
			if (r_out > 3 && l_out > 3)
			{
				//此处将下线拟合补充上线
				float a;
				a = ((float)right[r_out] - right[2]) / ((float)r_out - 2.0);
				if ((int)right[r_out] + a * (row - 2 - r_out) > col - 2 || (int)right[r_out] + a * (row - 2 - r_out) < 1)
					r_in = col - 2;
				else
					r_in = right[r_out] + a * (row - 2 - r_out);
				a = ((float)left[l_out] - left[2]) / ((float)l_out - 2.0);
				if ((int)left[l_out] + a * (row - 2 - l_out) > col - 2 || (int)left[l_out] + a * (row - 2 - l_out) < 1)
					l_in = 1;
				else
					l_in = left[l_out] + a * (row - 2 - l_out);
				supplements(side_line, row - 2, r_in, r_out, right[r_out]);
				supplements(side_line, row - 2, l_in, l_out, left[l_out]);
				mid_seeks(side_line, mid_line);
				mid_value(mid_line, side_line);
				return 3;
			}
			else
				return 7;
		}
		if (r_in && r_out && l_in && l_out)			//全十字
		{
			supplements(side_line, r_in, right[r_in], r_out, right[r_out]);
			supplements(side_line, l_in, left[l_in], l_out, left[l_out]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 3;
		}

		//过环判断位

		if (l_out && !r_out && !r_in)
		{
			//cout << "过环判断位" << endl;

			for (i = left[l_out + 1] + 1, mark = 0; i < left[l_out]; i++)
			{
				for (j = 0; l_out - j && side_line[l_out - j][col - 1 - i] != 2; j++);
				mark += j;
			}
			if (mark >= Round_pass)
			{
				//触发为入环延迟，延迟结束后触发入环
				round_in_delay = Round_in_unuse_delay;
			}

			//        ips114_showstr(0,5,"round_mark");
			//         ips114_showint16(8*13,5,mark);
			supplements(side_line, l_out, left[l_out], mid_max, left[mid_max]);
			mid_seeks(side_line, mid_line);
			mid_value(mid_line, side_line);
			return 2;
		}
	}
	return 4;
}
