// Copyright (c) 2018 Microsoft Corporation
// Licensed under the MIT license.
// Author: Paul Koch <code@koch.ninja>

#ifndef HISTOGRAM_BUCKET_VECTOR_ENTRY_H
#define HISTOGRAM_BUCKET_VECTOR_ENTRY_H

#include <type_traits> // std::is_pod

#include "ebmcore.h" // FractionalDataType
#include "EbmInternal.h" // EBM_INLINE
#include "Logging.h" // EBM_ASSERT & LOG

template<bool bClassification>
struct HistogramBucketVectorEntry;

template<>
struct HistogramBucketVectorEntry<true> final {
   // classification version of the HistogramBucketVectorEntry class

   FractionalDataType m_sumResidualError;
   // TODO: for single features, we probably want to just do a single pass of the data and collect our sumDenominator during that sweep.  This is probably also true for pairs since calculating pair sums can be done fairly efficiently, but for tripples and higher dimensions we might be better off calculating JUST the sumResidualError which is the only thing required for choosing splits and we could then do a second pass of the data to find the denominators once we know the splits.  Tripples and higher dimensions tend to re-add/subtract the same cells many times over which is why it might be better there.  Test these theories out on large datasets
   FractionalDataType m_sumDenominator;

   EBM_INLINE FractionalDataType GetSumDenominator() const {
      return m_sumDenominator;
   }
   EBM_INLINE void SetSumDenominator(FractionalDataType sumDenominatorSet) {
      m_sumDenominator = sumDenominatorSet;
   }
   EBM_INLINE void Add(const HistogramBucketVectorEntry<true> & other) {
      m_sumResidualError += other.m_sumResidualError;
      m_sumDenominator += other.m_sumDenominator;
   }
   EBM_INLINE void Subtract(const HistogramBucketVectorEntry<true> & other) {
      m_sumResidualError -= other.m_sumResidualError;
      m_sumDenominator -= other.m_sumDenominator;
   }
   EBM_INLINE void Copy(const HistogramBucketVectorEntry<true> & other) {
      m_sumResidualError = other.m_sumResidualError;
      m_sumDenominator = other.m_sumDenominator;
   }
   EBM_INLINE void AssertZero() const {
      EBM_ASSERT(0 == m_sumResidualError);
      EBM_ASSERT(0 == m_sumDenominator);
   }
};

template<>
struct HistogramBucketVectorEntry<false> final {
   // regression version of the HistogramBucketVectorEntry class

   FractionalDataType m_sumResidualError;

   EBM_INLINE FractionalDataType GetSumDenominator() const {
      EBM_ASSERT(false); // this should never be called, but the compiler seems to want it to exist
      return FractionalDataType { 0 };
   }
   EBM_INLINE void SetSumDenominator(FractionalDataType sumDenominator) {
      UNUSED(sumDenominator);
      EBM_ASSERT(false); // this should never be called, but the compiler seems to want it to exist
   }
   EBM_INLINE void Add(const HistogramBucketVectorEntry<false> & other) {
      m_sumResidualError += other.m_sumResidualError;
   }
   EBM_INLINE void Subtract(const HistogramBucketVectorEntry<false> & other) {
      m_sumResidualError -= other.m_sumResidualError;
   }
   EBM_INLINE void Copy(const HistogramBucketVectorEntry<false> & other) {
      m_sumResidualError = other.m_sumResidualError;
   }
   EBM_INLINE void AssertZero() const {
      EBM_ASSERT(0 == m_sumResidualError);
   }
};

static_assert(std::is_pod<HistogramBucketVectorEntry<false>>::value, "HistogramBucketVectorEntry will be more efficient as a POD as we make potentially large arrays of them!");
static_assert(std::is_pod<HistogramBucketVectorEntry<true>>::value, "HistogramBucketVectorEntry will be more efficient as a POD as we make potentially large arrays of them!");

#endif // HISTOGRAM_BUCKET_VECTOR_ENTRY_H
