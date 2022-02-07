#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

#define ASSERT_EQUAL( x, y )                                        \
{                                                                   \
  if( ( x ) != ( y ) )                                              \
  {                                                                 \
    std::cout <<            (   std::string("ASSERT FAILED: ")      \
                              + std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __FUNCTION__ )         \
                              + std::string( ": " )                 \
                              + std::to_string( ( x ) )             \
                              + std::string( " != " )               \
                              + std::to_string( ( y ) )             \
    ); test_failed = true;                                          \
  }                                                                 \
}


#define ASSERT_TRUE( condition )                                    \
{                                                                   \
  if( !( condition ) )                                              \
  {                                                                 \
    std::cout <<            (   std::string("ASSERT FAILED: ")      \
                              + std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __FUNCTION__ )         \
                              + std::string( "\n" )                 \
    ); test_failed = true;                                          \
  }                                                                 \
}

#define EXPECT_EXCEPTION( expression, exception )                   \
{                                                                   \
  try                                                               \
  {                                                                 \
    ( expression );                                                 \
  }                                                                 \
  catch( exception& e )                                             \
  {                                                                 \
    (void)e; /* to supress compiler warning: unused variable */     \
  }                                                                 \
  catch( ... )                                                      \
  {                                                                 \
    std::cout <<            (   std::string("ASSERT FAILED: ")      \
                              + std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __FUNCTION__ )         \
                              + std::string( "\n" )                 \
    ); test_failed = true;                                          \
  }                                                                 \
}

#define TEST_BEGIN( name )\
{\
  std::cerr << "-- Running test \"" << name << "\"..."; \
} \
bool test_failed = false; 

#define TEST_END() \
{\
  std::cerr << "finished\n"; return test_failed;\
}

