#pragma once

#include "../std/string.hpp"
#include "../std/vector.hpp"
#include "../std/utility.hpp"
#include "../std/set.hpp"

namespace downloader
{

class ChunksDownloadStrategy
{
public:
  typedef pair<int64_t, int64_t> RangeT;
  typedef set<RangeT> RangesContainerT;

private:
  int64_t m_chunkSize;
  static RangeT const INVALID_RANGE;
  /// <server url, currently downloading range or INVALID_RANGE if url is not used>
  typedef vector<pair<string, RangeT> > ServersT;
  ServersT m_servers;
  RangesContainerT m_chunksToDownload;

public:
  /// @param[in] chunksToDownload used for resume
  ChunksDownloadStrategy(vector<string> const & urls, int64_t fileSize, int64_t chunkSize = 512 * 1024);

  int64_t ChunkSize() const { return m_chunkSize; }
  /// Should be called when each chunk is completed
  void ChunkFinished(bool successfully, int64_t begRange, int64_t endRange);
  enum ResultT
  {
    ENextChunk,
    ENoFreeServers,
    EDownloadFailed,
    EDownloadSucceeded
  };
  /// Should be called until returns ENextChunk
  ResultT NextChunk(string & outUrl, int64_t & begRange, int64_t & endRange);

  void SetChunksToDownload(RangesContainerT & chunks);
  RangesContainerT const & ChunksLeft() const { return m_chunksToDownload; }
};

} // namespace downloader
