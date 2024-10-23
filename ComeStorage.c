#include "Recognition.h"

uint8 comestorages(uint8(*side_line)[col])
{
	int16 i, j;
	uint8 jump_mark = 0;
	uint8 mid_line[row] = { 0 };
	uint8 right[row] = { 0 };
	uint8 left[row] = { 0 };
	uint8 right_point = 1;
	uint8 left_point = 1;


	//寻边最高点
	for (i = row - 2; i > 1; i--)
	{
		for (j = col - 2; j > 1; j--)
		{
			if (side_line[i][j] == 2)
			{
				side_max = i;
				break;
			}
		}
		if (j != 1)
			break;

	}
    if(Sta_ED==-1)
    {
        if(j<2)
        {
            angular_c=END_angularss;

        return 88;
        }
    }

	//cout << "Staside_max=" << side_max << endl;
	if (side_max < StaEmax)
	{
		sta_end = 1;
		return 3;
	}
	mid_seek(side_line, mid_line, right, left);

	if (Sta_ED == 1)
	{

		for (i = side_max - 1; i > 2; i--)
		{
			if (right[i] + Stajp < right[i - 1])
			{
				if (jump_mark == 0)
					right_point = i;
				jump_mark++;
			}
		}
		//cout << "jump_mark=" << jump_mark << endl;
		if (jump_mark == 1)
		{
			//cout << "right_point=" << right_point << endl;
			if (right_point <= StaImax)
			{
				for (j = 1; side_line[1][j] != 2; j++);
				angular_c = right[right_point];
				angular_c -= j;
				angular_c *= Staes1;
				return 1;
			}
			return 4;
		}
		else
		{
			float a;
			if (side_line[1][2] == 2)
			{
				for (j = 2; side_line[j][1] == 2; j++);
				j--;
				//cout << side_line[j][1] << endl;
				//side_line[1][j] = 4;
				//side_line[side_max - 2][left[side_max - 2]] = 5;
				a = atan(((double)left[side_max - 2] - 1.0) / ((double)side_max - 1.0 - (double)j));
				//cout << "左边线角度为：" << a / PI * 180 << endl;
				if (a / PI * 180 < StaAmax)
				{
					angular_c = 0;
				}
				else
				{
					angular_c = left[side_max - 2];
					angular_c -= 1;
					angular_c *= Staes2;
				}
				return 2;

			}
			else
			{
				//cout << 111 << endl;
				for (j = 1; side_line[1][j] != 2; j++);

				a = atan(((double)left[side_max - 2] - (double)j) / ((double)side_max - 3.0));
				if (a / PI * 180 < StaAmax)
				{
					angular_c = 0;
				}
				else
				{
					angular_c = left[side_max - 2];
					angular_c -= j;
					angular_c *= Staes2;
				}
				return 2;

			}

		}
	}
	else
	{
		for (i = side_max - 1; i > 2; i--)
		{
			if (left[i]  > left[i - 1]+ Stajp)
			{
				if (jump_mark == 0)
					left_point = i;
				jump_mark++;
			}
		}
		//cout << "jump_mark=" << jump_mark << endl;
		if (jump_mark == 1)
		{
			//cout << "right_point=" << right_point << endl;
			if (left_point <= StaImax)
			{
				for (j = col-2; side_line[1][j] != 2; j--);
				angular_c = left[left_point];
				angular_c -= j;
				angular_c *= Staes1;
				return 1;
			}
			return 4;
		}
		else
		{
			float a;
			if (side_line[1][2] == 2)
			{
				for (j = 2; side_line[j][col-2] == 2; j++);
				j--;
				a = atan(( 1.0- (double)right[side_max - 2]) / ((double)side_max - 1.0 - (double)j));

				if (a / PI * 180 < StaAmax)
				{
					angular_c = 0;
				}
				else
				{
					angular_c = right[side_max - 2];
					angular_c -= 1;
					angular_c *= Staes2;
				}
				return 2;

			}
			else
			{
				//cout << 111 << endl;
				for (j = col-2; side_line[1][j] != 2; j--);

				a = atan(((double)j - (double)left[side_max - 2]) / ((double)side_max - 3.0));
				if (a / PI * 180 < StaAmax)
				{
					angular_c = 0;
				}
				else
				{
					angular_c = left[side_max - 2];
					angular_c -= j;
					angular_c *= Staes2;
				}
				return 2;

			}

		}
	}
	return 0;
}
