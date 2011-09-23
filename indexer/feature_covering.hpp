#pragma once
#include "point_to_int64.hpp"

#include "../geometry/rect2d.hpp"

#include "../base/base.hpp"

#include "../std/utility.hpp"
#include "../std/vector.hpp"

class FeatureType;

namespace covering
{
  typedef vector<pair<int64_t, int64_t> > IntervalsT;

  // Cover feature with RectIds and return their integer representations.
  vector<int64_t> CoverFeature(FeatureType const & feature,
                               int cellDepth,
                               uint64_t cellPenaltyArea);

  void AppendLowerLevels(RectId id, int cellDepth, IntervalsT & intervals);

  // Cover viewport with RectIds and append their RectIds as well.
  void CoverViewportAndAppendLowerLevels(m2::RectD const & rect, int cellDepth,
                                         IntervalsT & intervals);

  // Given a vector of intervals [a, b), sort them and merge overlapping intervals.
  IntervalsT SortAndMergeIntervals(IntervalsT const & intervals);

  RectId GetRectIdAsIs(m2::RectD const & r);

  // Calculate cell coding depth according to max visual scale for mwm.
  int GetCodingDepth(pair<int, int> const & scalesR);
}
