#ifndef CharQueueTest_h
#define CharQueueTest_h

#include <cppunit/extensions/HelperMacros.h>
#include "../src/char_queue.h"

class CharQueueTest : public CPPUNIT_NS::TestFixture {
  CPPUNIT_TEST_SUITE( CharQueueTest );
  CPPUNIT_TEST( test_push );
  CPPUNIT_TEST( test_pop_with_nothing );
  CPPUNIT_TEST( test_pop_after_push );
  CPPUNIT_TEST( test_pop_after_two_pushes );
  CPPUNIT_TEST( test_pop_after_two_pushes_and_a_pop );
  CPPUNIT_TEST( test_size_when_empty );
  CPPUNIT_TEST( test_size_with_one_item );
  CPPUNIT_TEST( test_size_with_two_items );
  CPPUNIT_TEST( test_size_after_a_push_and_a_pop );
  CPPUNIT_TEST( test_size_after_two_pushes_and_a_pop );
  CPPUNIT_TEST( test_tripple_pop_after_double_push );
  CPPUNIT_TEST( test_clear_with_nothing );
  CPPUNIT_TEST( test_clear_after_two_pushes );
  CPPUNIT_TEST_SUITE_END();

public:
  CharQueue *char_queue;

  void setUp() {
    char_queue = new CharQueue();
  }

  void tearDown() {
    delete char_queue;
  }

  void test_push() {
    char_queue->push('h');
  }

  void test_pop_with_nothing() {
    CPPUNIT_ASSERT_EQUAL( '\0', char_queue->pop() );
  }

  void test_pop_after_push() {
    char_queue->push('h');
    CPPUNIT_ASSERT_EQUAL('h', char_queue->pop());
  }

  void test_pop_after_two_pushes() {
    char_queue->push('x');
    char_queue->push('y');
    CPPUNIT_ASSERT_EQUAL( 'x', char_queue->pop() );
  }

  void test_pop_after_two_pushes_and_a_pop() {
    char_queue->push('x');
    char_queue->push('y');
    char_queue->pop();
    CPPUNIT_ASSERT_EQUAL( 'y', char_queue->pop() );
  }

  void test_pop_after_a_push_and_a_pop() {
    char_queue->push('x');
    char_queue->pop();
    CPPUNIT_ASSERT_EQUAL( '\0', char_queue->pop() );
  }

  void test_size_when_empty() {
    CPPUNIT_ASSERT_EQUAL( 0, char_queue->size() );
  }

  void test_size_with_one_item() {
    char_queue->push('h');
    CPPUNIT_ASSERT_EQUAL( 1, char_queue->size() );
  }

  void test_size_with_two_items() {
    char_queue->push('h');
    char_queue->push('x');
    CPPUNIT_ASSERT_EQUAL( 2, char_queue->size() );
  }

  void test_size_after_a_push_and_a_pop() {
    char_queue->push('h');
    char_queue->pop();
    CPPUNIT_ASSERT_EQUAL( 0, char_queue->size() );
  }

  void test_size_after_two_pushes_and_a_pop() {
    char_queue->push('h');
    char_queue->push('x');
    char_queue->pop();
    CPPUNIT_ASSERT_EQUAL( 1, char_queue->size() );
  }

  void test_size_after_a_pop_when_empty() {
    char_queue->pop();
    CPPUNIT_ASSERT_EQUAL( 0, char_queue->size() );
  }

  void test_tripple_pop_after_double_push() {
    char_queue->push('f');
    char_queue->push('b');
    CPPUNIT_ASSERT_EQUAL( 'f', char_queue->pop() );
    CPPUNIT_ASSERT_EQUAL( 'b', char_queue->pop() );
    CPPUNIT_ASSERT_EQUAL( '\0', char_queue->pop() );
  }

  void test_clear_with_nothing() {
    char_queue->clear();
    CPPUNIT_ASSERT_EQUAL( '\0', char_queue->pop() );
    CPPUNIT_ASSERT_EQUAL( 0, char_queue->size() );
  }

  void test_clear_after_two_pushes() {

    char_queue->push('h');
    char_queue->push('r');
    char_queue->clear();
    CPPUNIT_ASSERT_EQUAL( '\0', char_queue->pop() );
    CPPUNIT_ASSERT_EQUAL( 0, char_queue->size() );
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( CharQueueTest );

#endif
