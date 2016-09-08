/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#ifndef YoSingleton_h
#define YoSingleton_h

#include <assert.h>

#include "yo_pattern.h"
#include <iostream>
#include <string.h>

namespace yo {
namespace common {

template<typename T>
class YoSingleton : public YoPattern
{
	static T* ms_singleton;
	public:
		YoSingleton()
		{
			//std::cout << "1" << std::endl;
			assert(!ms_singleton);
			//use a cunning trick to get the singleton pointing to the start of the whole, rather than
			//the start of the CSingleton part of the object

			//int offset = (int)(T*)1 - (int)(YoSingleton <T>*)(T*)1;
			//ms_singleton = (T*)this;

			//std::cout << "2" << std::endl;
			ms_singleton = (T*)(this);

			//std::cout << "3" << std::endl;
		}
		~YoSingleton()
		{
			assert(ms_singleton);
			ms_singleton = 0;
		}
		/*
		 *
        **/
		static inline void create()
		{
			//std::cout << "4" << std::endl;
			if(ms_singleton)
				return;

			//std::cout << "5" << std::endl;
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

template <typename T> T* YoSingleton <T>::ms_singleton = 0;

} // namespace common
} // namespace elc
#endif	// #ifndef ElcSingleton_h
