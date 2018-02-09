typedef struct
{
	float SetTragetTemper; // 定义设定值
	float ActualTemper; // 定义实际值
	float err; // 定义偏差值
	float err_next; // 定义上一个偏差值
	float err_last; // 定义最上前的偏差值
	float Kp,Ki,Kd; // 定义比例、积分、微分系数
}PID;

PID pid;


void PID_init(void)
{
	pid.SetTragetTemper=0.0;
	pid.ActualTemper=0.0;
	pid.err=0.0;
	pid.err_last=0.0;
	pid.err_next=0.0;
	pid.Kp=0.2;
	pid.Ki=0.015;
	pid.Kd=0.2;
}

float PID_realize(float TragetTemper , float ActualTemper)
{
	float incrementSpeed = 0;
	pid.SetTragetTemper = TragetTemper;
	pid.ActualTemper = ActualTemper;
	pid.err = pid.SetTragetTemper - pid.ActualTemper;
	incrementSpeed = pid.Kp * (pid.err - pid.err_next) + pid.Ki*pid.err
	+ pid.Kd*(pid.err - 2*pid.err_next + pid.err_last);
	pid.ActualTemper += incrementSpeed;
	pid.err_last = pid.err_next;
	pid.err_next = pid.err;
	return pid.ActualTemper;
}



