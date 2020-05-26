/* 
Copyright (c) 2019, Lawrence Livermore National Security, LLC
and DESUL project contributors. See the COPYRIGHT file for details.
Source: https://github.com/desul/desul

SPDX-License-Identifier: (BSD-3-Clause)
*/

#ifndef DESUL_ATOMICS_COMPARE_EXCHANGE_GCC_HPP_
#define DESUL_ATOMICS_COMPARE_EXCHANGE_GCC_HPP_
#include "desul/atomics/Common.hpp"

#ifdef DESUL_HAVE_GCC_ATOMICS
#if !defined(DESUL_HAVE_16BYTE_COMPARE_AND_SWAP) && !defined(__CUDACC__)
// This doesn't work in WSL??
//#define DESUL_HAVE_16BYTE_COMPARE_AND_SWAP
#endif
namespace desul {
template<class MemoryScope>
void atomic_thread_fence(MemoryOrderAcquire, MemoryScope) {
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
}

template<class MemoryScope>
void atomic_thread_fence(MemoryOrderRelease, MemoryScope) {
  __atomic_thread_fence(__ATOMIC_RELEASE);
}

template <typename T, class MemoryScope>
T atomic_compare_exchange(
    T* dest, T compare, T value, MemoryOrderRelaxed, MemoryScope) {
  (void)__atomic_compare_exchange_n(
      dest, &compare, value, false, __ATOMIC_RELAXED, __ATOMIC_RELAXED);
  return compare;
}
template <typename T, class MemoryScope>
T atomic_compare_exchange(
    T* dest, T compare, T value, MemoryOrderSeqCst, MemoryScope) {
  (void)__atomic_compare_exchange_n(
      dest, &compare, value, false, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
  return compare;
}
template <typename T, class MemoryScope>
T atomic_compare_exchange(
    T* dest, T compare, T value, MemoryOrderAcquire, MemoryScope) {
  (void)__atomic_compare_exchange_n(
      dest, &compare, value, false, __ATOMIC_ACQUIRE, __ATOMIC_ACQUIRE);
  return compare;
}
template <typename T, class MemoryScope>
T atomic_compare_exchange(
    T* dest, T compare, T value, MemoryOrderRelease, MemoryScope) {
  (void)__atomic_compare_exchange_n(
      dest, &compare, value, false, __ATOMIC_RELEASE, __ATOMIC_RELAXED);
  return compare;
}
template <typename T, class MemoryScope>
T atomic_compare_exchange(
    T* dest, T compare, T value, MemoryOrderAcqRel, MemoryScope) {
  (void)__atomic_compare_exchange_n(
      dest, &compare, value, false, __ATOMIC_ACQ_REL, __ATOMIC_ACQUIRE);
  return compare;
}
}  // namespace desul
#endif
#endif
