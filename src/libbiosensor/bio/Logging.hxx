/*
 * Copyright 2011 Karolis Petrauskas
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef BIO_Logging_HXX
#define BIO_Logging_HXX
#include <iostream>


#if defined(LOG_LEVEL_ALL)
#define LOG_LEVEL 7
#elif defined(LOG_LEVEL_TRACE)
#define LOG_LEVEL 6
#elif defined(LOG_LEVEL_DEBUG)
#define LOG_LEVEL 5
#elif defined(LOG_LEVEL_INFO)
#define LOG_LEVEL 4
#elif defined(LOG_LEVEL_WARN)
#define LOG_LEVEL 3
#elif defined(LOG_LEVEL_ERROR)
#define LOG_LEVEL 2
#elif defined(LOG_LEVEL_FATAL)
#define LOG_LEVEL 1
#elif defined(LOG_LEVEL_NONE)
#define LOG_LEVEL 0
#else
#define LOG_LEVEL 4
#endif


#if LOG_LEVEL >= 6
#define LOG_TRACE(statement) std::clog << "TRACE  " << statement << std::endl;
#else
#define LOG_TRACE(statement) ;
#endif

#if LOG_LEVEL >= 5
#define LOG_DEBUG(statement) std::clog << "DEBUG  " << statement << std::endl;
#else
#define LOG_DEBUG(statement) ;
#endif

#if LOG_LEVEL >= 4
#define LOG_INFO(statement) std::clog << "INFO   " << statement << std::endl;
#else
#define LOG_INFO(statement) ;
#endif

#if LOG_LEVEL >= 3
#define LOG_WARN(statement) std::clog << "WARN   " << statement << std::endl;
#else
#define LOG_WARN(statement) ;
#endif

#if LOG_LEVEL >= 2
#define LOG_ERROR(statement) std::clog << "ERROR  " << statement << std::endl;
#else
#define LOG_ERROR(statement) ;
#endif

#if LOG_LEVEL >= 1
#define LOG_FATAL(statement) std::clog << "FATAL  " << statement << std::endl;
#else
#define LOG_FATAL(statement) ;
#endif


#endif /* BIO_Logging_HXX */
