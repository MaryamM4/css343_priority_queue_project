/**
 * COVIDPriorityQueue (Header file)
 * CSS 343 HW 1: Priority Queue
 * ==============================
 * Maintain a priority queue for covid vaccination that
 * is determined based on the following:
 *
 * - Age of the patient (Older patients get higher priority)-
 *   patients under 5 are not enlisted into the queue.
 *
 * - Existing illnesses (you can assume this is a binary field
 *   that has the highest priority)
 * ==============================
 * Implemented by Maryam M, 2024
 */

#pragma once

#include <queue>

template <typename ItemType> class COVIDPriorityQueue {
public:
  COVIDPriorityQueue();
  ~COVIDPriorityQueue();

  std::priority_queue<ItemType>();

  bool empty() const;
  void push(const ItemType &newEntry);
  void pop();
  ItemType &top();
};