#include "block/block.h"
#include "vm/boc.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "block-db.h"
#include "block-auto.h"
#include "validator/collator.h"
#include "vm/cp0.h"

using td::Ref;

int verbosity;

struct IntError {
  std::string err_msg;
  IntError(std::string _msg) : err_msg(_msg) {
  }
  IntError(const char* _msg) : err_msg(_msg) {
  }
};

std::string binary_file_to_string(std::string filename) {
  int fd = open(filename.c_str(), O_RDONLY);
  if (fd < 0) {
    throw IntError{std::string{"cannot open file `"} + filename + "`"};
  }
  long long size = lseek(fd, 0, SEEK_END);
  if (size < 0) {
    close(fd);
    throw IntError{std::string{"file `"} + filename + "` is not a regular file"};
  }
  if (!size) {
    close(fd);
    return "";
  }
  std::string res;
  res.resize(size + 1);
  long long r = pread(fd, const_cast<char*>(res.data()), size + 1, 0);
  close(fd);
  if (r != size) {
    throw IntError{std::string{"error reading file `"} + filename + "`"};
  }
  res.pop_back();
  return res;
}

td::Ref<vm::Cell> load_boc(std::string filename) {
  std::cerr << "loading bag-of-cell file " << filename << std::endl;
  std::string bytes = binary_file_to_string(filename);
  vm::BagOfCells boc;
  auto res = boc.deserialize(td::Slice{bytes});
  if (res.is_error()) {
    throw IntError{(PSLICE() << "cannot deserialize bag-of-cells " << res.error()).c_str()};
  }
  if (res.ok() <= 0 || boc.get_root_cell().is_null()) {
    throw IntError{"cannot deserialize bag-of-cells "};
  }
  return boc.get_root_cell();
}

void test1() {
  block::ShardId id{ton::masterchainId}, id2{ton::basechainId, 0x11efULL << 48};
  std::cout << '[' << id << "][" << id2 << ']' << std::endl;
  vm::CellBuilder cb;
  cb << id << id2;
  std::cout << "ShardIdent.pack() = " << block::tlb::t_ShardIdent.pack(cb, {12, 3, 0x3aeULL << 52}) << std::endl;
  std::cout << cb << std::endl;
  auto cref = cb.finalize();
  td::Ref<vm::CellSlice> cs{true, cref}, cs2;
  block::ShardId id3{cs.write()}, id4, id5;
  cs >> id4 >> id5;
  std::cout << '[' << id3 << "][" << id4 << "][" << id5 << ']' << std::endl;
  vm::CellSlice csl{std::move(cref)};
  std::cout << "ShardIdent.get_size() = " << block::tlb::t_ShardIdent.get_size(csl) << std::endl;
  std::cout << "MsgAddress.get_size() = " << block::tlb::t_MsgAddress.get_size(csl) << std::endl;
  std::cout << "Grams.get_size() = " << block::tlb::t_Grams.get_size(csl) << std::endl;
  std::cout << "Grams.as_integer() = " << block::tlb::t_Grams.as_integer(csl) << std::endl;
  (csl + 8).print_rec(std::cout);
  std::cout << "Grams.get_size() = " << block::tlb::t_Grams.get_size(csl + 8) << std::endl;
  std::cout << "Grams.as_integer() = " << block::tlb::t_Grams.as_integer(csl + 8) << std::endl;

  vm::CellSlice csl2{csl};
  block::gen::ShardIdent::Record sh_id;
  for (int i = 0; i < 3; i++) {
    std::cout << csl2 << std::endl;
    bool ok = tlb::unpack(csl2, sh_id);
    std::cout << "block::gen::ShardIdent.unpack() = " << ok << std::endl;
    if (ok) {
      std::cout << "  (shard_ident shard_pfx_bits:" << sh_id.shard_pfx_bits << " workchain_id:" << sh_id.workchain_id
                << " shard_prefix:" << std::hex << sh_id.shard_prefix << std::dec << ")" << std::endl;
    }
  }

  block::tlb::ShardIdent::Record shard_id;
  for (int i = 0; i < 3; i++) {
    std::cout << "ShardIdent.validate() = " << block::tlb::t_ShardIdent.validate(csl) << std::endl;
    csl.print_rec(std::cerr);
    csl.dump(std::cerr, 7);
    std::cout << "ShardIdent.unpack() = " << block::tlb::t_ShardIdent.unpack(csl, shard_id) << std::endl;
    if (shard_id.is_valid()) {
      std::cout << "shard_pfx_bits:" << shard_id.shard_pfx_bits << " workchain_id:" << shard_id.workchain_id
                << " shard_prefix:" << shard_id.shard_prefix << std::endl;
    }
  }
  std::cout << "ShardIdent.skip_validate() = " << block::tlb::t_ShardIdent.validate_skip(csl) << std::endl;
  std::cout << "ShardIdent.skip_validate() = " << block::tlb::t_ShardIdent.validate_skip(csl) << std::endl;
  std::cout << "ShardIdent.skip_validate() = " << block::tlb::t_ShardIdent.validate_skip(csl) << std::endl;
  using namespace td::literals;
  std::cout << "Grams.store_intval(239) = " << block::tlb::t_Grams.store_integer_value(cb, "239"_i256) << std::endl;
  std::cout << "Grams.store_intval(17239) = " << block::tlb::t_Grams.store_integer_value(cb, "17239"_i256) << std::endl;
  std::cout << "Grams.store_intval(-17) = " << block::tlb::t_Grams.store_integer_value(cb, "-17"_i256) << std::endl;
  std::cout << "Grams.store_intval(0) = " << block::tlb::t_Grams.store_integer_value(cb, "0"_i256) << std::endl;
  std::cout << cb << std::endl;
  cs = td::Ref<vm::CellSlice>{true, cb.finalize()};
  std::cout << "Grams.store_intval(666) = " << block::tlb::t_Grams.store_integer_value(cb, "666"_i256) << std::endl;
  std::cout << cb << std::endl;
  cs2 = td::Ref<vm::CellSlice>{true, cb.finalize()};
  std::cout << "Grams.validate(cs) = " << block::tlb::t_Grams.validate(*cs) << std::endl;
  std::cout << "Grams.validate(cs2) = " << block::tlb::t_Grams.validate(*cs2) << std::endl;
  //
  block::gen::SplitMergeInfo::Record data;
  block::gen::Grams::Record data2;
  std::cout << "block::gen::Grams.validate(cs) = " << block::gen::t_Grams.validate(*cs) << std::endl;
  std::cout << "block::gen::Grams.validate(cs2) = " << block::gen::t_Grams.validate(*cs2) << std::endl;
  std::cout << "[cs = " << cs << "]" << std::endl;
  bool ok = tlb::csr_unpack_inexact(cs, data);
  std::cout << "block::gen::SplitMergeInfo.unpack(cs, data) = " << ok << std::endl;
  if (ok) {
    std::cout << "  cur_shard_pfx_len = " << data.cur_shard_pfx_len << "; acc_split_depth = " << data.acc_split_depth
              << "; this_addr = " << data.this_addr << "; sibling_addr = " << data.sibling_addr << std::endl;
  }
  ok = tlb::csr_unpack_inexact(cs, data2);
  std::cout << "block::gen::Grams.unpack(cs, data2) = " << ok << std::endl;
  if (ok) {
    std::cout << "  amount = " << data2.amount << std::endl;
    block::gen::VarUInteger::Record data3;
    ok = tlb::csr_type_unpack(data2.amount, block::gen::t_VarUInteger_16, data3);
    std::cout << "  block::gen::VarUInteger16.unpack(amount, data3) = " << ok << std::endl;
    if (ok) {
      std::cout << "    len = " << data3.len << "; value = " << data3.value << std::endl;
      vm::CellBuilder cb;
      std::cout << "    block::gen::VarUInteger16.pack(cb, data3) = "
                << tlb::type_pack(cb, block::gen::t_VarUInteger_16, data3) << std::endl;
      std::cout << "    cb = " << cb.finalize() << std::endl;
    }
  }
  {
    vm::CellBuilder cb;
    td::BitArray<256> hash;
    memset(hash.data(), 0x69, 32);
    bool ok = tlb::pack(
        cb, block::gen::Test::Record{1000000000000, {170239, -888, {239017, "1000000000000000000"_ri256}, hash}, 17});
    std::cout << "  block::gen::Test::pack(cb, {1000000000000, ...}) = " << ok << std::endl;
    std::cout << "  cb = " << cb << std::endl;
    auto cell = cb.finalize();
    vm::CellSlice cs{cell};
    cs.print_rec(std::cout);
    block::gen::Test::Record data;
    std::cout << "  block::gen::Test::validate_ref(cell) = " << block::gen::t_Test.validate_ref(cell) << std::endl;
    ok = tlb::unpack(cs, data);
    std::cout << "  block::gen::Test::unpack(cs, data) = " << ok << std::endl;
    if (ok) {
      std::cout << "a:" << data.a << " b:" << data.r1.b << " c:" << data.r1.c << " d:" << data.r1.r1.d
                << " e:" << data.r1.r1.e << " f:" << data.r1.f << " g:" << data.g << std::endl;
    }
    std::cout << "  block::gen::Test::print_ref(cell) = ";
    block::gen::t_Test.print_ref(std::cout, cell, 2);
    block::gen::t_CurrencyCollection.print_ref(std::cout, cell, 2);
    std::cout << std::endl;
  }
  std::cout << "Grams.add_values() = " << block::tlb::t_Grams.add_values(cb, cs.write(), cs2.write()) << std::endl;
  std::cout << cb << std::endl;
  std::cout << "block::gen::t_HashmapAug_64_...print_type() = " << block::gen::t_HashmapAug_64_Ref_Transaction_Grams
            << std::endl;
  std::cout << "block::gen::t_...print_type() = "
            << block::gen::t_HashmapAugE_32_Ref_BinTreeAug_True_CurrencyCollection_CurrencyCollection << std::endl;
}

void test2(vm::CellSlice& cs) {
  std::cout << "Bool.validate() = " << block::tlb::t_Bool.validate(cs) << std::endl;
  std::cout << "UInt16.validate() = " << block::tlb::t_uint16.validate(cs) << std::endl;
  std::cout << "HashmapE(32,UInt16).validate() = " << block::tlb::HashmapE(32, block::tlb::t_uint16).validate(cs)
            << std::endl;
  std::cout << "block::gen::HashmapE(32,UInt16).validate() = "
            << block::gen::HashmapE{32, block::gen::t_uint16}.validate(cs) << std::endl;
}

std::string block_db_dir;
bool block_db_create;
td::actor::ActorOwn<block::BlockDb> block_db;
bool stop = false;

std::vector<Ref<vm::Cell>> ext_msgs;

void block_db_test(std::unique_ptr<block::ZerostateInfo> zerostate) {
  assert(vm::init_op_cp0());
  td::actor::Scheduler scheduler({2});
  scheduler.run_in_context([&] {
    auto res = block::BlockDb::create_block_db(block_db_dir, std::move(zerostate), block_db_create);
    if (!res.is_ok()) {
      std::cerr << "fatal: cannot initialize block database `" << block_db_dir << "`: " << res.error().to_string()
                << std::endl;
      exit(3);
    }
    block_db = res.move_as_ok();
    auto collator = ton::Collator::create_collator(block_db.get(), ton::masterchainId, (1ULL << 63));
    for (auto msg : ext_msgs) {
      td::actor::send_closure(collator, &ton::Collator::register_external_message_cell, msg,
                              [msg](td::Result<bool> res) -> void {
                                if (res.is_error()) {
                                  LOG(ERROR) << "cannot register external message : " << res.error().to_string();
                                } else {
                                  LOG(INFO) << "external message registered, result = " << res.move_as_ok();
                                }
                              });
    }
    td::actor::send_closure(
        collator, &ton::Collator::generate_block_candidate, ton::masterchainId, (1ULL << 63),
        [&](td::Result<ton::BlockCandidate> res) -> void {
          if (res.is_error()) {
            LOG(ERROR) << "cannot generate new block: " << res.move_as_error();
            stop = true;
          } else {
            ton::BlockCandidate candidate = res.move_as_ok();
            std::cerr << "new block candidate generated: file_hash=" << candidate.id.file_hash.to_hex()
                      << " size=" << candidate.data.size() << std::endl;
            td::actor::send_closure(block_db, &block::BlockDb::save_new_block, candidate.id.id, candidate.id.root_hash,
                                    candidate.id.file_hash, std::move(candidate.data), 128,
                                    [&](td::Result<td::Unit> res) -> void {
                                      if (res.is_error()) {
                                        LOG(ERROR) << "cannot save new block to disk: " << res.move_as_error();
                                      } else {
                                        LOG(INFO) << "block saved";
                                        stop = true;
                                      }
                                    });
          }
        });
    // block_db.release();
    collator.release();
  });
  int i = 10;
  while (scheduler.run(1) && i-- > 0 && !stop) {
  }
}

void usage() {
  std::cout << "usage: test-block [-B<block-base-dir>][-z<zerostate-boc-file>][-Z<zerostate-hash>][-c] "
               "[<boc-file>]\n\tor test-block -h\n";
  exit(2);
}

int main(int argc, char* const argv[]) {
  int i;
  int new_verbosity_level = VERBOSITY_NAME(INFO);
  auto zerostate = std::make_unique<block::ZerostateInfo>();
  while ((i = getopt(argc, argv, "B:cF:hv:z:Z:")) != -1) {
    switch (i) {
      case 'B':
        block_db_dir = optarg;
        break;
      case 'c':
        block_db_create = true;
        break;
      case 'v':
        new_verbosity_level = VERBOSITY_NAME(FATAL) + (verbosity = td::to_integer<int>(td::Slice(optarg)));
        break;
      case 'z':
        zerostate->filename = optarg;
        break;
      case 'Z':
        if (!block::parse_hash_string(optarg, zerostate->root_hash)) {
          std::cerr << "invalid zero state root hash (must consist of 64 hexadecimal digits)\n";
          usage();
        }
        break;
      case 'F':
        if (!block::parse_hash_string(optarg, zerostate->file_hash)) {
          std::cerr << "invalid zero state file hash (must consist of 64 hexadecimal digits)\n";
          usage();
        }
        break;
      case 'h':
        usage();
        exit(2);
      default:
        usage();
        exit(2);
    }
  }
  SET_VERBOSITY_LEVEL(new_verbosity_level);
  try {
    if (!block_db_dir.empty()) {
      while (optind < argc) {
        ext_msgs.push_back(load_boc(argv[optind++]));
      }
      block_db_test(std::move(zerostate));
      return 0;
    }
    td::Ref<vm::Cell> boc;
    if (optind < argc) {
      boc = load_boc(argv[optind]);
    }
    if (boc.not_null()) {
      vm::CellSlice cs{vm::NoVm(), boc};
      cs.print_rec(std::cout);
      test2(cs);
    } else {
      test1();
    }
  } catch (IntError& err) {
    std::cerr << "caught internal error " << err.err_msg << std::endl;
    return 1;
  }
  return 0;
}
