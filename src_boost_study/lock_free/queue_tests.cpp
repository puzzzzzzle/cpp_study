//
// Created by khalidzhang on 2019/11/25.
//

#include <atomic>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/thread.hpp>
#include <functional>
#include <thread>

#include "common_includes.h"

// config

void producer_worker(std::atomic_int *m_producer_count,
                     boost::lockfree::queue<int> *m_queue, int allWorkers) {
  for (int i = 0; i < allWorkers; ++i) {
    int value = ++(*m_producer_count);
    while (!m_queue->push(value))
      ;
  }
}

void consumer_worker(std::atomic_int *m_consumer_count,
                     boost::lockfree::queue<int> *m_queue,
                     const std::atomic_bool *done) {
  int value;
  while (!(*done)) {
    while (m_queue->pop(value)) ++(*m_consumer_count);
  }

  while (m_queue->pop(value)) ++(*m_consumer_count);
}

void test_impl(const int iterations, int producer, int consumer) {
  std::atomic_int m_producer_count(0);
  std::atomic_int m_consumer_count(0);
  std::atomic_bool done(false);
  boost::lockfree::queue<int> m_queue(128);

  auto producer_thread_worker = [&] {
    return producer_worker(&m_producer_count, &m_queue, iterations);
  };  // lambda
  auto consumer_thread_worker = [&] {
    return consumer_worker(&m_consumer_count, &m_queue, &done);
  };  // equal as bind
  //    auto consumer_thread_worker = std::bind(consumer_worker,
  //    &m_consumer_count, &m_queue,&done);              // equal as bind

  boost::thread_group producer_threads, consumer_threads;

  for (int i = 0; i != producer; ++i)
    producer_threads.create_thread(producer_thread_worker);

  for (int i = 0; i != consumer; ++i)
    consumer_threads.create_thread(consumer_thread_worker);

  producer_threads.join_all();
  done = true;
  consumer_threads.join_all();

  ASSERT_EQ(m_producer_count, m_consumer_count);
  ASSERT_EQ(m_producer_count, iterations * producer);
  ASSERT_EQ(m_consumer_count, iterations * producer);
}

const int m_iterations = 10000 * 1000;

TEST(producer_consumer, 100_100) {
  int producer = 100;
  int consumer = 100;
  int iterations = m_iterations / producer;
  test_impl(iterations, producer, consumer);
}

TEST(producer_consumer, 1_100) {
  int producer = 1;
  int consumer = 100;
  int iterations = m_iterations / producer;
  test_impl(iterations, producer, consumer);
}

TEST(producer_consumer, 100_1) {
  int producer = 100;
  int consumer = 1;
  int iterations = m_iterations / producer;
  test_impl(iterations, producer, consumer);
}

TEST(producer_consumer, 1_1) {
  int producer = 1;
  int consumer = 1;
  int iterations = m_iterations / producer;
  test_impl(iterations, producer, consumer);
}

TEST(producer_consumer, 4_1) {
  int producer = 4;
  int consumer = 1;
  int iterations = m_iterations / producer;
  test_impl(iterations, producer, consumer);
}

TEST(producer_consumer, 1_4) {
  int producer = 1;
  int consumer = 4;
  int iterations = m_iterations / producer;
  test_impl(iterations, producer, consumer);
}

TEST(producer_consumer, 4_4) {
  int producer = 4;
  int consumer = 4;
  int iterations = m_iterations / producer;
  test_impl(iterations, producer, consumer);
}