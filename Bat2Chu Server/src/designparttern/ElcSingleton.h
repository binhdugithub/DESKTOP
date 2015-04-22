/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#ifndef ElcSingleton_h
#define ElcSingleton_h

#include <assert.h>

#include "ElcDesignPattern.h"

template<typename T>
class ElcSingleton : public ElcDesignPattern
{
	static T* ms_singleton;
	public:
		ElcSingleton()
		{
			assert(!ms_singleton);
			//use a cunning trick to get the singleton pointing to the start of the whole, rather than
			//the start of the CSingleton part of the object
			int offset = (int)(T*)1 - (int)(ElcSingleton <T>*)(T*)1;
			ms_singleton = (T*)((int)this + offset);
		}
		~ElcSingleton()
		{
			assert(ms_singleton);
			ms_singleton = 0;
		}
		/*
		 *
        **/
		static inline void create()
		{
			if(ms_singleton)
				return;
			new T();
		}
		/*
		 *
        **/
		static inline void destroy()
		{
			if(ms_singleton)
				delete ms_singleton;
			ms_singleton=0;
		}
		/*!
			Aquire singleton (reference)
		*/
		static inline T& getSingleton()
		{
			assert(ms_singleton);
			return *ms_singleton;
		}

		/*!
			Aquire singleton (pointer)
		*/
		static T* getSingletonPtr()
		{
			//assert(ms_singleton);
			create();
			return ms_singleton;
		}
};

template <typename T> T* ElcSingleton <T>::ms_singleton = 0;


#endif	// #ifndef ElcSingleton_h