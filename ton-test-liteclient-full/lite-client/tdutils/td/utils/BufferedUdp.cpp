#include "td/utils/BufferedUdp.h"

char disable_linker_warning_about_empty_file_buffered_udp_cpp TD_UNUSED;

namespace td {

#if TD_PORT_POSIX
TD_THREAD_LOCAL detail::UdpReader *BufferedUdp::udp_reader_;
#endif

}  // namespace td
