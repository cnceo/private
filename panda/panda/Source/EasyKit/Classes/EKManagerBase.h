//// Copyright 1998-2014 xsj Games, Inc. All Rights Reserved.
//
//#pragma once
//
//
//template < typename T >
//class Singleton
//{
//
//public:
//	static T &GetInstance()
//	{
//		Init();
//		return *instance_;
//	}
//
//private:
//	static void Init()
//	{
//		if (instance_ == 0)
//		{
//			if (instance_ == 0)
//			{
//				instance_ = new T;
//				atexit(Destroy);    //�������ʱ����ע��ĺ���
//			}
//		}
//	}
//
//	static void Destroy()
//	{
//		delete instance_;
//	}
//
//	Singleton(const Singleton &other);
//	Singleton &operator=(const Singleton &other);
//	Singleton();
//	~Singleton();
//
//	static T * volatile instance_;
//};
//
//template < typename T >
//T * volatile Singleton < T >::instance_ = nullptr;
//
//
///**
//*  ����������
//*/
//
//class EKManagerBase
//{
//
//public:
//
//	~EKManagerBase();
//
//	float f_ElapsedTime;
//
//	virtual bool Init()=0;
//
//	virtual void Tick(float inDeltaTime)=0;
//
//	virtual void Enter();
//
//	virtual void Leave();
//
//	virtual void Register();
//
//};