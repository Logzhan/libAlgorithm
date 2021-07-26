// algorihtmTool.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>

#define BUFF_LEN  800

int   buffer[BUFF_LEN];
float res[BUFF_LEN] = {0.0f};
float res1[BUFF_LEN] = { 0.0f };

void bufferSlideAvg(int* buff){
	for (int j = 0; j <= 700; j++)
	{
		float avg = 0.0f;
		for (int k = j; k < (j + 100); k++){
			
			if (j == 700)printf("buff[%d]=%d\n", k, buff[k]);
			avg += buff[k];
		}
		avg /= 100.0f;
		res[j] = avg;
	}
	//printf("res = %f a = %d\n", res[j]);

	for (int j = 0; j <= 700; j++)
	{
		if (j == 0){
			float avg = 0.0f;
			for (int k = j; k < (j + 100); k++){

				if (j == 700)printf("buff[%d]=%d\n", k, buff[k]);
				avg += buff[k];
			}
			avg /= 100.0f;
			res1[j] = avg;
		}else{
			res1[j] = (res1[j - 1] * 100 - buff[j - 1] + buff[j + 99]) / 100;
		}

	/*	float avg = 0.0f;
		for (int k = j; k < (j + 100); k++){

			if (j == 700)printf("buff[%d]=%d\n", k, buff[k]);
			avg += buff[k];
		}
		avg /= 100.0f;
		res[j] = avg;*/
	}
}

void bufferSlideAvg1(int* buff, int buffLen,int winSize){
	
	// 方法1
	for (int j = 0; j <= buffLen - winSize; j++){
		res[j] = 0.0f;
		for (int k = j; k < (j + winSize); k++){
			res[j] += buff[k];
		}
		res[j] /= (float)winSize;
	}

	// 方法2(优化重复计算)
	for (int j = 0; j <= buffLen - winSize; j++){
		if (j == 0){
			res1[j] = 0.0f;
			for (int k = j; k < (j + winSize); k++){
				res1[j] += buff[k];
			}
			res1[j] /= (float)winSize;
		}
		else{
			//res1[j] = (res1[j - 1] * winSize - buff[j - 1] + buff[j - 1 + winSize]) / winSize;
			res1[j] = res1[j-1] + (buff[j-1+winSize] - buff[j-1]) / (float)winSize;
		}
	}
}




int _tmain(int argc, _TCHAR* argv[])
{
	for (int i = 0; i < BUFF_LEN; i++){
		buffer[i] = i+1;
	}

	for (int i = 0; i < BUFF_LEN; i++){
		printf("buffer[%d] = %d\n", i, buffer[i]);
	}
	bufferSlideAvg1(buffer, BUFF_LEN, 100);

	for (int i = 0; i < BUFF_LEN; i++){
		printf("res[%d] = %f res1[%d] = %f\n", i, res[i], i, res1[i]);
	}

	system("pause");
	return 0;
}

