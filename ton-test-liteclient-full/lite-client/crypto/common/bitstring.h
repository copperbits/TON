#pragma once
#include "common/refcnt.hpp"
#include <utility>
#include <array>
#include <string>
#include <ostream>
#include <cstdlib>

namespace td {
template <class Pt>
struct BitPtrGen;

typedef BitPtrGen<unsigned char> BitPtr;
typedef BitPtrGen<const unsigned char> ConstBitPtr;

struct BitstringError {};

namespace bitstring {

void bits_memcpy(unsigned char* to, int to_offs, const unsigned char* from, int from_offs, std::size_t bit_count);
void bits_memcpy(BitPtr to, ConstBitPtr from, std::size_t bit_count);
void bits_memset(unsigned char* to, int to_offs, bool val, std::size_t bit_count);
void bits_memset(BitPtr to, bool val, std::size_t bit_count);
int bits_memcmp(const unsigned char* bs1, int bs1_offs, const unsigned char* bs2, int bs2_offs, std::size_t bit_count,
                std::size_t* same_upto = 0);
int bits_memcmp(ConstBitPtr bs1, ConstBitPtr bs2, std::size_t bit_count, std::size_t* same_upto = 0);
int bits_lexcmp(const unsigned char* bs1, int bs1_offs, std::size_t bs1_bit_count, const unsigned char* bs2,
                int bs2_offs, std::size_t bs2_bit_count);
int bits_lexcmp(ConstBitPtr bs1, std::size_t bs1_bit_count, ConstBitPtr bs2, std::size_t bs2_bit_count);
std::size_t bits_memscan(const unsigned char* ptr, int offs, std::size_t bit_count, bool cmp_to);
std::size_t bits_memscan_rev(const unsigned char* ptr, int offs, std::size_t bit_count, bool cmp_to);
std::size_t bits_memscan(ConstBitPtr bs, std::size_t bit_count, bool cmp_to);
std::size_t bits_memscan_rev(ConstBitPtr bs, std::size_t bit_count, bool cmp_to);
void bits_store_long_top(unsigned char* to, int to_offs, unsigned long long val, unsigned top_bits);
void bits_store_long_top(BitPtr to, unsigned long long val, unsigned top_bits);
void bits_store_long(BitPtr to, unsigned long long val, unsigned bits);
unsigned long long bits_load_long_top(const unsigned char* from, int from_offs, unsigned top_bits);
unsigned long long bits_load_long_top(ConstBitPtr from, unsigned top_bits);
long long bits_load_long(ConstBitPtr from, unsigned bits);
unsigned long long bits_load_ulong(ConstBitPtr from, unsigned bits);
long parse_bitstring_hex_literal(unsigned char* buff, std::size_t buff_size, const char* str, const char* str_end);
long parse_bitstring_binary_literal(BitPtr buff, std::size_t buff_size, const char* str, const char* str_end);

void bits_sha256(BitPtr to, ConstBitPtr from, std::size_t size);

std::string bits_to_binary(const unsigned char* ptr, int offs, std::size_t len);
std::string bits_to_binary(ConstBitPtr bs, std::size_t len);
std::string bits_to_hex(const unsigned char* ptr, int offs, std::size_t len);
std::string bits_to_hex(ConstBitPtr bs, std::size_t len);

}  // namespace bitstring

template <class Pt>
struct BitPtrGen {
  Pt* ptr;
  int offs;
  BitPtrGen(Pt* _ptr, int _offs = 0) : ptr(_ptr), offs(_offs) {
  }
  template <class Pt2>
  BitPtrGen(BitPtrGen<Pt2> val) : ptr(val.ptr), offs(val.offs) {
  }
  BitPtrGen& operator+=(int _offs) {
    offs += _offs;
    return *this;
  }
  BitPtrGen& operator-=(int _offs) {
    offs -= _offs;
    return *this;
  }
  void advance(int _offs) {
    offs += _offs;
  }
  bool byte_aligned() const {
    return !(offs & 7);
  }
  Pt* get_byte_ptr() const {
    return ptr + (offs >> 3);
  }
  void copy_from(BitPtrGen<const Pt> from, unsigned size) const {
    bitstring::bits_memcpy(*this, from, size);
  }
  BitPtrGen& concat(BitPtrGen<const Pt> from, unsigned size) {
    bitstring::bits_memcpy(*this, from, size);
    offs += size;
    return *this;
  }
  void fill(bool bit, unsigned size) {
    bitstring::bits_memset(*this, bit, size);
  }
  BitPtrGen& concat_same(bool bit, unsigned size) {
    bitstring::bits_memset(*this, bit, size);
    offs += size;
    return *this;
  }
  int compare(BitPtrGen<const Pt> other, std::size_t size, std::size_t* same_upto = nullptr) const {
    return bitstring::bits_memcmp(*this, other, size, same_upto);
  }
  long long get_int(unsigned bits) const {
    return bitstring::bits_load_long(*this, bits);
  }
  unsigned long long get_uint(unsigned bits) const {
    return bitstring::bits_load_ulong(*this, bits);
  }
  void store_uint(unsigned long long val, unsigned n) const {
    bitstring::bits_store_long(*this, val, n);
  }
  void store_int(long long val, unsigned n) const {
    bitstring::bits_store_long(*this, val, n);
  }
  BitPtrGen operator+(int _offs) const {
    return BitPtrGen{ptr, offs + _offs};
  }
  BitPtrGen operator-(int _offs) const {
    return BitPtrGen{ptr, offs - _offs};
  }
  BitPtrGen operator++() {
    ++offs;
    return *this;
  }
  BitPtrGen operator--() {
    --offs;
    return *this;
  }
  BitPtrGen operator++(int) {
    return BitPtrGen{ptr, offs++};
  }
  BitPtrGen operator--(int) {
    return BitPtrGen{ptr, offs--};
  }
  bool is_null() const {
    return !ptr;
  }
  bool not_null() const {
    return ptr;
  }
  class BitSelector {
    Pt* ptr;
    unsigned char mask;

   public:
    BitSelector(Pt* _ptr, int offs) {
      ptr = _ptr + (offs >> 3);
      mask = (unsigned char)(0x80 >> (offs & 7));
    }
    bool clear() {
      *ptr = (unsigned char)(*ptr & ~mask);
      return false;
    }
    bool set() {
      *ptr = (unsigned char)(*ptr | mask);
      return true;
    }
    bool operator=(bool val) {
      return val ? set() : clear();
    }
    operator bool() const {
      return *ptr & mask;
    }
  };
  BitSelector operator*() const {
    return BitSelector{ptr, offs};
  }
  BitSelector operator[](int i) const {
    return BitSelector{ptr, offs + i};
  }
  std::string to_hex(std::size_t len) const {
    return bitstring::bits_to_hex(*this, len);
  }
  std::string to_binary(std::size_t len) const {
    return bitstring::bits_to_binary(*this, len);
  }
};

template <class Rf, class Pt>
class BitSliceGen {
  Rf ref;
  Pt* ptr;
  unsigned offs, len;

 public:
  struct BitSliceError {};
  BitSliceGen() : ref(), ptr(0), offs(0), len(0) {
  }
  BitSliceGen(Rf _ref, Pt* _ptr, int _offs, unsigned _len)
      : ref(std::move(_ref)), ptr(_ptr + (_offs >> 3)), offs(_offs & 7), len(_len) {
  }
  BitSliceGen(const BitSliceGen& bs, unsigned _offs, unsigned _len);
  BitSliceGen(BitSliceGen&& bs, unsigned _offs, unsigned _len);
  BitSliceGen(Pt* _ptr, unsigned _len) : ref(Rf{false}), ptr(_ptr), offs(0), len(_len) {
  }
  ~BitSliceGen() {
  }
  Pt* get_ptr() const {
    return ptr;
  }
  BitPtrGen<Pt> get_bitptr() const {
    return BitPtrGen<Pt>{ptr, (int)offs};
  }
  bool is_valid() const {
    return ptr != 0;
  }
  unsigned char cur_byte() const {
    return *ptr;
  }
  unsigned get_offs() const {
    return offs;
  }
  unsigned size() const {
    return len;
  }
  unsigned byte_size() const {
    return (offs + len + 7) >> 3;
  }
  void ensure_throw(bool cond) const {
    if (!cond) {
      throw BitSliceError{};
    }
  }
  BitSliceGen& assign(Rf _ref, Pt* _ptr, unsigned _offs, unsigned _len);
  void forget() {
    ref.clear();
    ptr = 0;
    offs = len = 0;
  }
  bool operator[](unsigned i) const {
    i += offs;
    return ptr[i >> 3] & (0x80 >> (i & 7));
  }
  bool at(unsigned i) const {
    ensure_throw(i < len);
    return operator[](i);
  }
  bool advance_bool(unsigned bits);
  bool set_size_bool(unsigned bits) {
    if (bits > len) {
      return false;
    }
    len = bits;
    return true;
  }
  BitSliceGen& advance(unsigned bits) {
    ensure_throw(advance_bool(bits));
    return *this;
  }
  BitSliceGen& set_size(unsigned bits) {
    ensure_throw(set_size_bool(bits));
    return *this;
  }
  BitSliceGen subslice(unsigned from, unsigned bits) const & {
    return BitSliceGen(*this, from, bits);
  }
  BitSliceGen subslice(unsigned from, unsigned bits) && {
    return BitSliceGen(*this, from, bits);
  }
  void copy_to(BitPtr to) const {
    bitstring::bits_memcpy(to, get_bitptr(), size());
  }
  std::string to_binary() const {
    return bitstring::bits_to_binary(ptr, offs, len);
  }
  std::string to_hex() const {
    return bitstring::bits_to_hex(ptr, offs, len);
  }
  void dump(std::ostream& os, bool nocr = false) const {
    os << "[" << offs << "," << len << "]";
    if (!nocr) {
      os << std::endl;
    }
  }

 protected:
  inline Pt& cur_byte_w() const {
    return *ptr;
  }
};

template <class Rf, class Pt>
BitSliceGen<Rf, Pt>::BitSliceGen(const BitSliceGen<Rf, Pt>& bs, unsigned from, unsigned bits) : ref() {
  if (from >= bs.size() || bits > bs.size() - from) {
    ptr = 0;
    offs = len = 0;
    return;
  }
  //bs.dump(std::cout, true);
  //std::cout << ".subslice(" << from << "," << bits << ") = ";
  ref = bs.ref;
  offs = bs.offs + from;
  ptr = bs.ptr + (offs >> 3);
  offs &= 7;
  len = bits;
  //dump(std::cout);
}

template <class Rf, class Pt>
BitSliceGen<Rf, Pt>::BitSliceGen(BitSliceGen&& bs, unsigned from, unsigned bits) : ref() {
  if (from >= bs.size() || bits > bs.size() - from) {
    ptr = 0;
    offs = len = 0;
    return;
  }
  ref = std::move(bs.ref);
  offs = bs.offs + from;
  ptr = bs.ptr + (offs >> 3);
  offs &= 7;
  len = bits;
}

template <class Rf, class Pt>
BitSliceGen<Rf, Pt>& BitSliceGen<Rf, Pt>::assign(Rf _ref, Pt* _ptr, unsigned _offs, unsigned _len) {
  ref = std::move(_ref);
  ptr = _ptr + (_offs >> 3);
  offs = (_offs & 7);
  len = _len;
  return *this;
}

template <class Rf, class Pt>
inline bool BitSliceGen<Rf, Pt>::advance_bool(unsigned bits) {
  if (len < bits) {
    return false;
  }
  len -= bits;
  offs += bits;
  ptr += (offs >> 3);
  offs &= 7;
  return true;
}

typedef BitSliceGen<RefAny, const unsigned char> BitSlice;

static inline std::string to_hex(const BitSlice& bs) {
  return bs.to_hex();
}

static inline std::string to_binary(const BitSlice& bs) {
  return bs.to_binary();
}

class BitSliceWrite : public BitSliceGen<RefAny, unsigned char> {
 public:
  struct LengthMismatch {};
  BitSliceWrite(RefAny _ref, unsigned char* _ptr, unsigned _offs, unsigned _len)
      : BitSliceGen<RefAny, unsigned char>(_ref, _ptr, _offs, _len) {
  }
  BitSliceWrite() : BitSliceGen<RefAny, unsigned char>() {
  }
  BitSliceWrite(unsigned char* _ptr, unsigned _len) : BitSliceGen<RefAny, unsigned char>(_ptr, _len) {
  }
  operator BitSlice&() {
    return *reinterpret_cast<BitSlice*>(this);
  }
  operator const BitSlice&() const {
    return *reinterpret_cast<const BitSlice*>(this);
  }
  const BitSliceWrite& operator=(const BitSlice& bs) const;
  const BitSliceWrite& operator=(bool val) const;
};

class BitString : public CntObject {
  unsigned char* ptr;
  unsigned offs, len, bytes_alloc;

 public:
  BitString() : ptr(0), offs(0), len(0), bytes_alloc(0) {
  }
  explicit BitString(const BitSlice& bs, unsigned reserve_bits = 0);
  explicit BitString(unsigned reserve_bits);
  ~BitString() {
    if (ptr) {
      free(ptr);
    }
  }
  operator BitSlice() const;
  BitString* make_copy() const override;
  unsigned size() const {
    return len;
  }
  unsigned byte_size() const {
    return (offs + len + 7) >> 3;
  }
  ConstBitPtr cbits() const {
    return ConstBitPtr{ptr, (int)offs};
  }
  ConstBitPtr bits() const {
    return ConstBitPtr{ptr, (int)offs};
  }
  BitPtr bits() {
    return BitPtr{ptr, (int)offs};
  }
  BitString& reserve_bits(unsigned req_bits);
  BitSliceWrite reserve_bitslice(unsigned req_bits);
  BitString& append(const BitSlice& bs);
  BitSlice subslice(unsigned from, unsigned bits) const;
  BitSliceWrite subslice_write(unsigned from, unsigned bits);
  std::string to_hex() const {
    return bitstring::bits_to_hex(cbits(), size());
  }
  std::string to_binary() const {
    return bitstring::bits_to_binary(cbits(), size());
  }
};

extern std::ostream& operator<<(std::ostream& os, const BitString& bs);
extern std::ostream& operator<<(std::ostream& os, Ref<BitString> bs_ref);

extern template class Ref<BitString>;
typedef Ref<BitString> BitStringRef;

template <unsigned n>
class BitArray {
  static constexpr unsigned m = (n + 7) >> 3;
  typedef std::array<unsigned char, m> byte_array_t;
  typedef unsigned char raw_byte_array_t[m];
  byte_array_t bytes;

 public:
  const unsigned char* data() const {
    return bytes.data();
  }
  unsigned char* data() {
    return bytes.data();
  }
  unsigned size() const {
    return n;
  }
  const byte_array_t& as_array() const {
    return bytes;
  }
  byte_array_t& as_array() {
    return bytes;
  }
  Slice as_slice() const {
    return Slice{data(), m};
  }
  MutableSlice as_slice() {
    return MutableSlice{data(), m};
  }
  ConstBitPtr cbits() const {
    return ConstBitPtr{data()};
  }
  ConstBitPtr bits() const {
    return ConstBitPtr{data()};
  }
  BitPtr bits() {
    return BitPtr{data()};
  }
  BitArray() = default;
  BitArray(const BitArray&) = default;
  BitArray(const byte_array_t& init_bytes) : bytes(init_bytes) {
  }
  explicit BitArray(const raw_byte_array_t init_bytes) {
    memcpy(data(), init_bytes, m);
  }
  BitArray(ConstBitPtr from) {
    bitstring::bits_memcpy(bits(), from, n);
  }
  template <int N = n, typename X = std::enable_if_t<N == n && N <= 64, int>>
  explicit BitArray(long long val) {
    bitstring::bits_store_long(bits(), val, n);
  }
  BitArray& operator=(const BitArray&) = default;
  BitArray& operator=(const byte_array_t& set_bytes) {
    bytes = set_bytes;
    return *this;
  }
  BitArray& operator=(ConstBitPtr from) {
    bitstring::bits_memcpy(bits(), from, n);
    return *this;
  }
  BitArray& operator=(const raw_byte_array_t set_byte_array) {
    memcpy(data(), set_byte_array, m);
    return *this;
  }
  BitSliceWrite write_bitslice() {
    return BitSliceWrite{data(), n};
  }
  BitSlice as_bitslice() const {
    return BitSlice{data(), n};
  }
  unsigned long long to_ulong() const {
    return bitstring::bits_load_ulong(bits(), n);
  }
  long long to_long() const {
    return bitstring::bits_load_long(bits(), n);
  }
  void store_ulong(unsigned long long val) {
    bitstring::bits_store_long(bits(), val, n);
  }
  void store_long(long long val) {
    bitstring::bits_store_long(bits(), val, n);
  }
  void set_same(bool v) {
    bytes.fill(static_cast<unsigned char>(v ? -1 : 0));
  }
  void set_zero() {
    set_same(0);
  }
  void set_ones() {
    set_same(1);
  }
  void clear() {
    set_zero();
  }
  bool is_zero() const {
    return bitstring::bits_memscan(cbits(), n, 0) == n;
  }
  std::string to_hex() const {
    return bitstring::bits_to_hex(cbits(), size());
  }
  std::string to_binary() const {
    return bitstring::bits_to_binary(cbits(), size());
  }
  int compare(const BitArray& other) const {
    return (n % 8 == 0) ? memcmp(data(), other.data(), n / 8) : bitstring::bits_memcmp(bits(), other.bits(), n);
  }
  bool operator==(const BitArray& other) const {
    return (n % 8 == 0) ? (bytes == other.bytes) : !bitstring::bits_memcmp(bits(), other.bits(), n);
  }
  bool operator!=(const BitArray& other) const {
    return (n % 8 == 0) ? (bytes != other.bytes) : bitstring::bits_memcmp(bits(), other.bits(), n);
  }
  bool operator<(const BitArray& other) const {
    return (n % 8 == 0) ? (bytes < other.bytes) : (bitstring::bits_memcmp(bits(), other.bits(), n) < 0);
  }
  int compare(ConstBitPtr other) const {
    return bitstring::bits_memcmp(bits(), other, n);
  }
  bool operator==(ConstBitPtr other) const {
    return !compare(other);
  }
  bool operator!=(ConstBitPtr other) const {
    return compare(other);
  }
  BitPtr::BitSelector operator[](int i) {
    return bits()[i];
  }
  bool operator[](int i) const {
    return cbits()[i];
  }
  void compute_sha256(BitPtr to) const {
    bitstring::bits_sha256(to, cbits(), n);
  }
  void compute_sha256(BitArray<256>& to) const {
    bitstring::bits_sha256(to.bits(), cbits(), n);
  }
  static inline BitArray zero() {
    BitArray x;
    x.set_zero();
    return x;
  }
};

using Bits256 = BitArray<256>;

template <unsigned n>
std::ostream& operator<<(std::ostream& os, BitArray<n> bits) {
  return os << bits.to_hex();
}

}  // namespace td
