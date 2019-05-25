#include "auto/tl/ton_api_json.h"

#include "auto/tl/ton_api.h"
#include "auto/tl/ton_api.hpp"

#include "tl/tl_json.h"

#include "td/utils/base64.h"
#include "td/utils/common.h"
#include "td/utils/Slice.h"

#include <unordered_map>

namespace ton {
namespace ton_api{
  using namespace td;
Result<int32> tl_constructor_from_string(ton_api::Hashable *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"hashable.bool", -815709156},
    {"hashable.int32", -743074986},
    {"hashable.int64", -405107134},
    {"hashable.int256", 975377359},
    {"hashable.bytes", 118742546},
    {"hashable.pair", -941266795},
    {"hashable.vector", -550190227},
    {"hashable.validatorSessionOldRound", 1479622531},
    {"hashable.validatorSessionRoundAttempt", -555220893},
    {"hashable.validatorSessionRound", -522103108},
    {"hashable.blockSignature", 937530018},
    {"hashable.sentBlock", -1111911125},
    {"hashable.sentBlockEmpty", -1628289361},
    {"hashable.vote", -1363203131},
    {"hashable.blockCandidate", 195670285},
    {"hashable.blockCandidateAttempt", 1063025931},
    {"hashable.cntVector", 187199288},
    {"hashable.cntSortedVector", 2073445977},
    {"hashable.validatorSession", 1746035669}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::TestObject *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"testObject", -1521006198},
    {"testString", -934972983},
    {"testInt", 731271633},
    {"testVectorBytes", 1267407827}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::adnl_Address *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"adnl.address.udp", 1728947943},
    {"adnl.address.udp6", -484613126},
    {"adnl.address.tcp", -1018034936},
    {"adnl.address.tcp6", 1520957383},
    {"adnl.address.tunnel", 1870715901}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::adnl_Message *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"adnl.message.packet", -1129650608},
    {"adnl.message.createChannel", -428620869},
    {"adnl.message.confirmChannel", 1625103721},
    {"adnl.message.custom", 541595893},
    {"adnl.message.nop", 402186202},
    {"adnl.message.reinit", 281150752},
    {"adnl.message.query", -1265895046},
    {"adnl.message.answer", 262964246}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::adnl_PacketHeader *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"adnl.packetHeader.secp256k1", 69996134},
    {"adnl.packetHeader.unenc", -1063535831},
    {"adnl.packetHeader.channel", 810999805}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::adnl_fileTransfer_Message *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"adnl.fileTransfer.request", -1580411891},
    {"adnl.fileTransfer.ack", 1969703669},
    {"adnl.fileTransfer.finish", 153778610},
    {"adnl.fileTransfer.data", 1797132051}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::adnl_id_Full *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"adnl.id.ed25519", -1977122418},
    {"adnl.id.aes", -1843301606},
    {"adnl.id.unenc", -781946142},
    {"adnl.id.overlay", 542300433}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::adnl_id_Pk *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"adnl.id.pk.unenc", -2134363424},
    {"adnl.id.pk.ed25519", -1860420410},
    {"adnl.id.pk.aes", 1558834017},
    {"adnl.id.pk.overlay", -271455862}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::catchain_BlockResult *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"catchain.blockNotFound", -1240397692},
    {"catchain.blockResult", -1658179513}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::catchain_Difference *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"catchain.difference", 336974282},
    {"catchain.differenceFork", 1227341935}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::catchain_block_inner_Data *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"catchain.block.data.badBlock", -1241359786},
    {"catchain.block.data.fork", 1685731922},
    {"catchain.block.data.nop", 1417852112},
    {"catchain.block.data.vector", 1688809258}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::dht_UpdateRule *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"dht.updateRule.signature", -861982217},
    {"dht.updateRule.anybody", 1633127956},
    {"dht.updateRule.nodes", 392837202},
    {"dht.updateRule.overlayNodes", -886296416}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::dht_ValueResult *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"dht.valueNotFound", -1570634392},
    {"dht.valueFound", -468912268}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::dht_config_Local *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"dht.config.local", 1981827695},
    {"dht.config.random.local", 1584494022}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::fer_Type *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"fer.raptorQ", -574559230},
    {"fer.simple", 955691373}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::overlay_Broadcast *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"overlay.fer.received", 1733556588},
    {"overlay.fer.completed", -455219751},
    {"overlay.unicast", 861097508},
    {"overlay.broadcast", -2016150757},
    {"overlay.broadcastFer", -712985988},
    {"overlay.broadcastFerShort", -2137243558},
    {"overlay.broadcastNotFound", -1786366428}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::overlay_config_Local *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"overlay.config.local", 784541096},
    {"overlay.config.random.local", 688042922}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::rldp_Message *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"rldp.message", 2098973982},
    {"rldp.query", -570402140},
    {"rldp.answer", -1543742461}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::rldp_MessagePart *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"rldp.messagePart", 163394346},
    {"rldp.confirm", -175973288},
    {"rldp.complete", -1140018497}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::test0_MasterchainBlockExtra *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"test0.masterchainBlockExtra.empty", -1793623372},
    {"test0.masterchainBlockExtra.extra", -2070859848}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::test0_MasterchainStateExtra *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"test0.masterchainStateExtra.empty", -1491361123},
    {"test0.masterchainStateExtra.extra", 2099087416}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::tonNode_BlockDescription *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"tonNode.blockDescriptionEmpty", -2088456555},
    {"tonNode.blockDescription", 1185009800}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::tonNode_Broadcast *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"tonNode.blockBroadcast", 179736316},
    {"tonNode.ihrMessageBroadcast", 1381868723},
    {"tonNode.externalMessageBroadcast", 1025185895},
    {"tonNode.newShardBlockBroadcast", 183696060}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::tonNode_Prepared *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"tonNode.prepared", -356205619},
    {"tonNode.notFound", -490521178}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::tonNode_PreparedProof *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"tonNode.preparedProofEmpty", -949370502},
    {"tonNode.preparedProof", 1235611381},
    {"tonNode.preparedProofLink", 1040134797}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::tonNode_PreparedState *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"tonNode.preparedState", 928762733},
    {"tonNode.notFoundState", 842598993}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::validatorSession_Message *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"validatorSession.message.startSession", -1767807279},
    {"validatorSession.message.finishSession", -879025437}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::validatorSession_round_Message *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"validatorSession.message.submittedBlock", 309732534},
    {"validatorSession.message.approvedBlock", 1571844585},
    {"validatorSession.message.commit", -1408065803},
    {"validatorSession.message.vote", -1707978297},
    {"validatorSession.message.precommit", -1470843566},
    {"validatorSession.message.empty", 1243619241}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::Object *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"hashable.bool", -815709156},
    {"hashable.int32", -743074986},
    {"hashable.int64", -405107134},
    {"hashable.int256", 975377359},
    {"hashable.bytes", 118742546},
    {"hashable.pair", -941266795},
    {"hashable.vector", -550190227},
    {"hashable.validatorSessionOldRound", 1479622531},
    {"hashable.validatorSessionRoundAttempt", -555220893},
    {"hashable.validatorSessionRound", -522103108},
    {"hashable.blockSignature", 937530018},
    {"hashable.sentBlock", -1111911125},
    {"hashable.sentBlockEmpty", -1628289361},
    {"hashable.vote", -1363203131},
    {"hashable.blockCandidate", 195670285},
    {"hashable.blockCandidateAttempt", 1063025931},
    {"hashable.cntVector", 187199288},
    {"hashable.cntSortedVector", 2073445977},
    {"hashable.validatorSession", 1746035669},
    {"testObject", -1521006198},
    {"testString", -934972983},
    {"testInt", 731271633},
    {"testVectorBytes", 1267407827},
    {"adnl.address.udp", 1728947943},
    {"adnl.address.udp6", -484613126},
    {"adnl.address.tcp", -1018034936},
    {"adnl.address.tcp6", 1520957383},
    {"adnl.address.tunnel", 1870715901},
    {"adnl.addressList", -736117392},
    {"adnl.message.packet", -1129650608},
    {"adnl.message.createChannel", -428620869},
    {"adnl.message.confirmChannel", 1625103721},
    {"adnl.message.custom", 541595893},
    {"adnl.message.nop", 402186202},
    {"adnl.message.reinit", 281150752},
    {"adnl.message.query", -1265895046},
    {"adnl.message.answer", 262964246},
    {"adnl.node", 620296016},
    {"adnl.nodes", -1576412330},
    {"adnl.packetContents", 672164373},
    {"adnl.packetHeader.secp256k1", 69996134},
    {"adnl.packetHeader.unenc", -1063535831},
    {"adnl.packetHeader.channel", 810999805},
    {"adnl.config.global", -1099988784},
    {"adnl.fileTransfer.request", -1580411891},
    {"adnl.fileTransfer.ack", 1969703669},
    {"adnl.fileTransfer.finish", 153778610},
    {"adnl.fileTransfer.data", 1797132051},
    {"adnl.id.ed25519", -1977122418},
    {"adnl.id.aes", -1843301606},
    {"adnl.id.unenc", -781946142},
    {"adnl.id.overlay", 542300433},
    {"adnl.id.pk.unenc", -2134363424},
    {"adnl.id.pk.ed25519", -1860420410},
    {"adnl.id.pk.aes", 1558834017},
    {"adnl.id.pk.overlay", -271455862},
    {"adnl.id.short", 1044342095},
    {"catchain.block", -699055756},
    {"catchain.blockNotFound", -1240397692},
    {"catchain.blockResult", -1658179513},
    {"catchain.blocks", 1357697473},
    {"catchain.difference", 336974282},
    {"catchain.differenceFork", 1227341935},
    {"catchain.firstblock", 281609467},
    {"catchain.sent", -84454993},
    {"catchain.blockUpdate", 593975492},
    {"catchain.block.data", -122903008},
    {"catchain.block.dep", 1511706959},
    {"catchain.block.id", 620665018},
    {"catchain.block.data.badBlock", -1241359786},
    {"catchain.block.data.fork", 1685731922},
    {"catchain.block.data.nop", 1417852112},
    {"catchain.block.data.vector", 1688809258},
    {"catchain.config.global", 361026880},
    {"catchain.config.local", 1394037726},
    {"config.global", -1606514086},
    {"config.local", 41976406},
    {"dht.key", -160964977},
    {"dht.keyDescription", 862674694},
    {"dht.message", -1140008050},
    {"dht.node", 1725249223},
    {"dht.nodes", 2037686462},
    {"dht.pong", 1519054721},
    {"dht.stored", 1881602824},
    {"dht.updateRule.signature", -861982217},
    {"dht.updateRule.anybody", 1633127956},
    {"dht.updateRule.nodes", 392837202},
    {"dht.updateRule.overlayNodes", -886296416},
    {"dht.value", -1867700277},
    {"dht.valueNotFound", -1570634392},
    {"dht.valueFound", -468912268},
    {"dht.config.global", -2066822649},
    {"dht.config.local", 1981827695},
    {"dht.config.random.local", 1584494022},
    {"dummydb.block", -944592423},
    {"dummydb.gcValidatorSessionList", -1602508432},
    {"dummyworkchain0.config.global", -631148845},
    {"dummyworkchain0.config.local", -1220354201},
    {"fer.raptorQ", -574559230},
    {"fer.simple", 955691373},
    {"id.config.local", 993556028},
    {"liteServer.accountId", 1973478085},
    {"liteServer.accountState", 1887029073},
    {"liteServer.blockData", -1519063700},
    {"liteServer.blockState", -1414669300},
    {"liteServer.currentTime", -380436467},
    {"liteServer.error", -1146494648},
    {"liteServer.masterchainInfo", -2055001983},
    {"liteServer.sendMsgStatus", 961602967},
    {"liteServer.debug.verbosity", 1564493619},
    {"liteclient.config.global", -285892428},
    {"liteserver.config.local", 1129790198},
    {"overlay.fer.received", 1733556588},
    {"overlay.fer.completed", -455219751},
    {"overlay.unicast", 861097508},
    {"overlay.broadcast", -2016150757},
    {"overlay.broadcastFer", -712985988},
    {"overlay.broadcastFerShort", -2137243558},
    {"overlay.broadcastNotFound", -1786366428},
    {"overlay.broadcastList", 416407263},
    {"overlay.message", 1965368352},
    {"overlay.node", -1284920910},
    {"overlay.nodes", -460904178},
    {"overlay.broadcastFer.id", -937343829},
    {"overlay.config.local", 784541096},
    {"overlay.config.random.local", 688042922},
    {"rldp.message", 2098973982},
    {"rldp.query", -570402140},
    {"rldp.answer", -1543742461},
    {"rldp.messagePart", 163394346},
    {"rldp.confirm", -175973288},
    {"rldp.complete", -1140018497},
    {"tcp.pong", -597034237},
    {"test0.proof", 288856343},
    {"test0.proofLink", 198411810},
    {"test0.shardchain.block", -1740890249},
    {"test0.shardchain.state", -1819502437},
    {"test.validatorSession.block", -1418990707},
    {"test0.blockSignatures", -1512447916},
    {"test0.extMessage", -424680397},
    {"test0.masterchainBlockExtra.empty", -1793623372},
    {"test0.masterchainBlockExtra.extra", -2070859848},
    {"test0.masterchainStateExtra.empty", -1491361123},
    {"test0.masterchainStateExtra.extra", 2099087416},
    {"test0.topShardBlockDescription", 939132390},
    {"test0.validatorSessionId", -1695860169},
    {"test0.validatorSet", -1877581587},
    {"test0.validatorSetItem", 408501132},
    {"test0.masterchain.shardInfo", 262681349},
    {"ton.blockId", -989106576},
    {"tonNode.blockDescriptionEmpty", -2088456555},
    {"tonNode.blockDescription", 1185009800},
    {"tonNode.blockIdExt", 1733487480},
    {"tonNode.blockSignature", 1357921331},
    {"tonNode.blockBroadcast", 179736316},
    {"tonNode.ihrMessageBroadcast", 1381868723},
    {"tonNode.externalMessageBroadcast", 1025185895},
    {"tonNode.newShardBlockBroadcast", 183696060},
    {"tonNode.data", 1443505284},
    {"tonNode.externalMessage", -596270583},
    {"tonNode.ihrMessage", 1161085703},
    {"tonNode.newShardBlock", 1375779283},
    {"tonNode.prepared", -356205619},
    {"tonNode.notFound", -490521178},
    {"tonNode.preparedProofEmpty", -949370502},
    {"tonNode.preparedProof", 1235611381},
    {"tonNode.preparedProofLink", 1040134797},
    {"tonNode.preparedState", 928762733},
    {"tonNode.notFoundState", 842598993},
    {"tonNode.sessionId", -880136334},
    {"tonNode.shardPublicOverlayId", -492335911},
    {"tonNode.zeroStateIdExt", 494024110},
    {"validator.config.global", -1525645549},
    {"validator.config.local", 1716256616},
    {"validatorSession.blockUpdate", -1836855753},
    {"validatorSession.candidate", 2100525125},
    {"validatorSession.candidateId", 436135276},
    {"validatorSession.id", -22534276},
    {"validatorSession.message.startSession", -1767807279},
    {"validatorSession.message.finishSession", -879025437},
    {"validatorSession.pong", -590989459},
    {"validatorSession.round.id", 2477989},
    {"validatorSession.message.submittedBlock", 309732534},
    {"validatorSession.message.approvedBlock", 1571844585},
    {"validatorSession.message.commit", -1408065803},
    {"validatorSession.message.vote", -1707978297},
    {"validatorSession.message.precommit", -1470843566},
    {"validatorSession.message.empty", 1243619241},
    {"validatorSession.candidate.id", -1126743751}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Result<int32> tl_constructor_from_string(ton_api::Function *object, const std::string &str) {
  static const std::unordered_map<Slice, int32, SliceHash> m = {
    {"catchain.getBlock", 155049336},
    {"catchain.getBlockHistory", -1470730762},
    {"catchain.getBlocks", 53062594},
    {"catchain.getDifference", -798175528},
    {"dht.findNode", 1826803307},
    {"dht.findValue", -1370791919},
    {"dht.getSignedAddressList", 960283782},
    {"dht.ping", -873775336},
    {"dht.query", 2102593385},
    {"dht.store", 882065938},
    {"getTestObject", 197109379},
    {"liteServer.debug.setVerbosity", 462775286},
    {"liteServer.getAccountState", 1804144165},
    {"liteServer.getBlock", 1668796173},
    {"liteServer.getMasterchainInfo", -1984567762},
    {"liteServer.getState", -1167184202},
    {"liteServer.getTime", 380459572},
    {"liteServer.query", 2039219935},
    {"liteServer.sendMessage", 1762317442},
    {"overlay.getBroadcast", 758510240},
    {"overlay.getBroadcastList", 1109141562},
    {"overlay.getRandomPeers", 1223582891},
    {"overlay.query", -855800765},
    {"tcp.ping", 1292381082},
    {"tonNode.downloadBlock", -495814205},
    {"tonNode.downloadBlockProof", 1272334218},
    {"tonNode.downloadBlockProofLink", 632488134},
    {"tonNode.downloadState", -738248612},
    {"tonNode.getNextBlockDescription", 341160179},
    {"tonNode.prepareBlock", 1973649230},
    {"tonNode.prepareBlockProof", -2024000760},
    {"tonNode.prepareState", -381168335},
    {"validatorSession.downloadCandidate", -520274443},
    {"validatorSession.ping", 1745111469}
  };
  auto it = m.find(str);
  if (it == m.end()) {
    return Status::Error("Unknown class");
  }
  return it->second;
}
Status from_json(ton_api::hashable_bool &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_int32 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_int64 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_int256 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_bytes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_pair &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "left", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.left_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "right", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.right_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_vector &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_validatorSessionOldRound &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signatures", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.signatures_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_validatorSessionRoundAttempt &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "votes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.votes_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "precommitted", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.precommitted_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_validatorSessionRound &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "locked_round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.locked_round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "locked_block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.locked_block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "precommitted", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.precommitted_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "approved_blocks", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.approved_blocks_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signatures", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.signatures_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "attempts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.attempts_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_blockSignature &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_sentBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.file_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "collated_data_file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.collated_data_file_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_sentBlockEmpty &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::hashable_vote &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "node", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.node_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_blockCandidate &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "approved", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.approved_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_blockCandidateAttempt &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "votes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.votes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_cntVector &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_cntSortedVector &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::hashable_validatorSession &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "old_rounds", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.old_rounds_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "cur_round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.cur_round_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::testObject &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "o", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.o_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "f", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.f_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::testString &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::testInt &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::testVectorBytes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_vector_bytes(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_address_udp &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "ip", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ip_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "port", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.port_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_address_udp6 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "ip", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ip_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "port", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.port_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_address_tcp &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "ip", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ip_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "port", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.port_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_address_tcp6 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "ip", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ip_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "port", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.port_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_address_tunnel &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "to", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.to_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "tunid", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.tunid_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_addressList &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "addrs", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.addrs_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "version", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.version_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_message_packet &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "packet", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.packet_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_message_createChannel &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.date_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_message_confirmChannel &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "peer_key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.peer_key_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.date_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_message_custom &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_message_nop &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::adnl_message_reinit &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.date_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_message_query &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "query_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.query_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "query", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.query_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_message_answer &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "query_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.query_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "answer", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.answer_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_node &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "addr_list", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.addr_list_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_nodes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_packetContents &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "rand1", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.rand1_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "flags", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.flags_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "from", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.from_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "from_short", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.from_short_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "message", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.message_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "messages", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.messages_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "address", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.address_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "recv_addr_list_version", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.recv_addr_list_version_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "confirm_seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.confirm_seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "reinit_date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.reinit_date_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "dst_reinit_date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dst_reinit_date_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "rand2", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.rand2_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_packetHeader_secp256k1 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "dst", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dst_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "point", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.point_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_packetHeader_unenc &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "dst", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dst_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_packetHeader_channel &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "dst", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dst_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_config_global &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "static_nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.static_nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_fileTransfer_request &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_fileTransfer_ack &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_fileTransfer_finish &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_fileTransfer_data &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "fer", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.fer_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_ed25519 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_aes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_unenc &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_overlay &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "name", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.name_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_pk_unenc &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_pk_ed25519 &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_pk_aes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_pk_overlay &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "name", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.name_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::adnl_id_short &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_block &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "incarnation", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.incarnation_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "height", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.height_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.data_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_blockNotFound &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::catchain_blockResult &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_blocks &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "blocks", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.blocks_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_difference &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "sent_upto", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.sent_upto_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_differenceFork &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "left", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.left_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "right", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.right_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_firstblock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "unique_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.unique_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_sent &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "cnt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.cnt_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_blockUpdate &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_block_data &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "prev", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.prev_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "deps", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.deps_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_block_dep &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "height", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.height_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.data_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_block_id &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "incarnation", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.incarnation_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "height", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.height_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.data_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_block_data_badBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_block_data_fork &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "left", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.left_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "right", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.right_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_block_data_nop &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::catchain_block_data_vector &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "msgs", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_vector_bytes(to.msgs_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_config_global &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "tag", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.tag_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "tag", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.tag_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::config_global &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "adnl", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.adnl_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "dht", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dht_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "catchains", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.catchains_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "dummy0", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dummy0_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validators", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validators_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "liteclients", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.liteclients_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "udp_ports", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.udp_ports_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "tcp_ports", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.tcp_ports_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "local_ids", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.local_ids_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "dht", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dht_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "public_overlays", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.public_overlays_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "catchains", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.catchains_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "dummy0", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.dummy0_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validators", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validators_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "liteservers", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.liteservers_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_key &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "name", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.name_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "idx", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.idx_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_keyDescription &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "update_rule", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.update_rule_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_message &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "node", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.node_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_node &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "addr_list", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.addr_list_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "version", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.version_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_nodes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_pong &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "random_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.random_id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_stored &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::dht_updateRule_signature &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::dht_updateRule_anybody &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::dht_updateRule_nodes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "max_nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.max_nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_updateRule_overlayNodes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "max_nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.max_nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_value &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.value_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "ttl", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ttl_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_valueNotFound &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_valueFound &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_config_global &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "static_nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.static_nodes_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "k", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.k_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "a", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.a_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_config_random_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "cnt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.cnt_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "addr_list", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.addr_list_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dummydb_block &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "flags", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.flags_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "prev", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.prev_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "next", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.next_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "lt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.lt_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "state", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.state_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "state_file", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.state_file_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "proof", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.proof_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "proof_link", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.proof_link_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signatures", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.signatures_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dummydb_gcValidatorSessionList &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "list", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.list_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dummyworkchain0_config_global &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "zero_state_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.zero_state_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dummyworkchain0_config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::fer_raptorQ &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "symbol_size", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.symbol_size_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "total_symbols", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.total_symbols_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "total_size", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.total_size_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::fer_simple &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "symbol_size", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.symbol_size_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "total_symbols", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.total_symbols_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "total_size", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.total_size_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::id_config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "addr_list", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.addr_list_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_accountId &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_accountState &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shardblk", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shardblk_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard_proof", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.shard_proof_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "proof", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.proof_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "state", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.state_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_blockData &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_blockState &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.file_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_currentTime &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "now", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.now_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_error &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "code", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.code_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "message", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.message_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_masterchainInfo &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "last", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.last_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "state_root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.state_root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "init", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.init_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_sendMsgStatus &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "status", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.status_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_debug_verbosity &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteclient_config_global &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "ip", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ip_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "port", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.port_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteserver_config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "port", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.port_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_fer_received &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_fer_completed &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_unicast &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_broadcast &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.date_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_broadcastFer &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "fer", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.fer_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.date_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_broadcastFerShort &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_broadcastNotFound &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::overlay_broadcastList &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hashes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hashes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_message &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "overlay", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.overlay_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_node &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "overlay", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.overlay_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "version", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.version_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_nodes &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "nodes", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.nodes_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_broadcastFer_id &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "type", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.type_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "date", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.date_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "name", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.name_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_config_random_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "cnt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.cnt_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "name", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.name_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "addr_list", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.addr_list_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::rldp_message &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::rldp_query &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "query_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.query_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::rldp_answer &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "query_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.query_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::rldp_messagePart &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "transfer_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.transfer_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "fer_type", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.fer_type_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "part", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.part_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "total_size", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.total_size_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::rldp_confirm &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "transfer_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.transfer_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "part", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.part_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::rldp_complete &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "transfer_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.transfer_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "part", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.part_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tcp_pong &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "random_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.random_id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_proof &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "link", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.link_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signatures", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.signatures_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_proofLink &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "prev", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.prev_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "state", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.state_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "split", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.split_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_shardchain_block &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "prev", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.prev_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "split", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.split_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "state", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.state_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "pad", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.pad_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "extra", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.extra_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_shardchain_state &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "split", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.split_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "extra", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.extra_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test_validatorSession_block &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "height", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.height_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_blockSignatures &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "signatures", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.signatures_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_extMessage &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_masterchainBlockExtra_empty &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::test0_masterchainBlockExtra_extra &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "randseed", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.randseed_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "rotate", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.rotate_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shards", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shards_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_masterchainStateExtra_empty &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::test0_masterchainStateExtra_extra &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_randseed", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_randseed_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "next_randseed", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.next_randseed_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "next_rotate_at", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.next_rotate_at_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "prev_blocks", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.prev_blocks_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shards", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shards_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "pool", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.pool_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_topShardBlockDescription &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "after_split", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.after_split_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "after_merge", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.after_merge_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "before_split", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.before_split_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signatures", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signatures_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_validatorSessionId &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard_from", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_from_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ts_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_validatorSet &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validators", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validators_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_validatorSetItem &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "weight", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.weight_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::test0_masterchain_shardInfo &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "last_block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.last_block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "before_merge", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.before_merge_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "before_split", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.before_split_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "after_merge", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.after_merge_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "after_split", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.after_split_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::ton_blockId &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "root_cell_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_cell_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.file_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_blockDescriptionEmpty &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::tonNode_blockDescription &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_blockIdExt &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.file_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_blockSignature &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "who", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.who_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_blockBroadcast &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "validator_set_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.validator_set_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signatures", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.signatures_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "masterchain_block_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.masterchain_block_id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "proof", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.proof_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_ihrMessageBroadcast &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "message", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.message_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_externalMessageBroadcast &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "message", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.message_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_newShardBlockBroadcast &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_data &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_externalMessage &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_ihrMessage &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_newShardBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_prepared &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::tonNode_notFound &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::tonNode_preparedProofEmpty &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::tonNode_preparedProof &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "masterchain_block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.masterchain_block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_preparedProofLink &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::tonNode_preparedState &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::tonNode_notFoundState &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::tonNode_sessionId &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "utime_from", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.utime_from_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "utime_to", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.utime_to_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_shardPublicOverlayId &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "shard", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.shard_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_zeroStateIdExt &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "workchain", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.workchain_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.file_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validator_config_global &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "zero_state_root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.zero_state_root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "zero_state_file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.zero_state_file_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validator_config_local &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_blockUpdate &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "ts", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.ts_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "actions", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.actions_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "state", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.state_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_candidate &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "collated_data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.collated_data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_candidateId &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "src", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.src_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.file_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "collated_data_file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.collated_data_file_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_id &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "slice", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.slice_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "start_time", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.start_time_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "end_time", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.end_time_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "participants", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.participants_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_startSession &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_finishSession &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::validatorSession_pong &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_round_id &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "session", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.session_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "height", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.height_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "prev_block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.prev_block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "seqno", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.seqno_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_submittedBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "root_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.root_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.file_hash_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "collated_data_file_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.collated_data_file_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_approvedBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "candidate", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.candidate_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_commit &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "candidate", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.candidate_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "signature", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.signature_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_vote &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "attempt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.attempt_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "candidate", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.candidate_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_precommit &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "attempt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.attempt_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "candidate", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.candidate_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_message_empty &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "attempt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.attempt_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_candidate_id &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "block_hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_getBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_getBlockHistory &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "height", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.height_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "stop_if", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.stop_if_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_getBlocks &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "blocks", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.blocks_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::catchain_getDifference &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "rt", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.rt_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_findNode &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "k", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.k_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_findValue &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "key", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.key_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "k", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.k_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_getSignedAddressList &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::dht_ping &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "random_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.random_id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_query &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "node", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.node_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::dht_store &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "value", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.value_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::getTestObject &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::liteServer_debug_setVerbosity &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "verbosity", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.verbosity_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_getAccountState &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "account", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.account_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_getBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_getMasterchainInfo &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::liteServer_getState &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_getTime &to, JsonObject &from) {
  return Status::OK();
}
Status from_json(ton_api::liteServer_query &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "data", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.data_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::liteServer_sendMessage &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "body", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json_bytes(to.body_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_getBroadcast &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_getBroadcastList &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "list", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.list_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_getRandomPeers &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "peers", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.peers_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::overlay_query &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "overlay", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.overlay_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tcp_ping &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "random_id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.random_id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_downloadBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_downloadBlockProof &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_downloadBlockProofLink &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_downloadState &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_getNextBlockDescription &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "prev_block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.prev_block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_prepareBlock &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_prepareBlockProof &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "allow_partial", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.allow_partial_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::tonNode_prepareState &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "block", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.block_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_downloadCandidate &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "round", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.round_, value));
    }
  }
  {
    TRY_RESULT(value, get_json_object_field(from, "id", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.id_, value));
    }
  }
  return Status::OK();
}
Status from_json(ton_api::validatorSession_ping &to, JsonObject &from) {
  {
    TRY_RESULT(value, get_json_object_field(from, "hash", JsonValue::Type::Null, true));
    if (value.type() != JsonValue::Type::Null) {
      TRY_STATUS(from_json(to.hash_, value));
    }
  }
  return Status::OK();
}
void to_json(JsonValueScope &jv, const ton_api::Hashable &object) {
  ton_api::downcast_call(const_cast<ton_api::Hashable &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::hashable_bool &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.bool");
  jo << ctie("value", ToJson(object.value_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_int32 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.int32");
  jo << ctie("value", ToJson(object.value_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_int64 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.int64");
  jo << ctie("value", ToJson(JsonInt64{object.value_}));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_int256 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.int256");
  jo << ctie("value", ToJson(object.value_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_bytes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.bytes");
  jo << ctie("value", ToJson(JsonBytes{object.value_}));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_pair &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.pair");
  jo << ctie("left", ToJson(object.left_));
  jo << ctie("right", ToJson(object.right_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_vector &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.vector");
  jo << ctie("value", ToJson(object.value_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSessionOldRound &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.validatorSessionOldRound");
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("block", ToJson(object.block_));
  jo << ctie("signatures", ToJson(object.signatures_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSessionRoundAttempt &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.validatorSessionRoundAttempt");
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("votes", ToJson(object.votes_));
  jo << ctie("precommitted", ToJson(object.precommitted_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSessionRound &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.validatorSessionRound");
  jo << ctie("locked_round", ToJson(object.locked_round_));
  jo << ctie("locked_block", ToJson(object.locked_block_));
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("precommitted", ToJson(object.precommitted_));
  jo << ctie("approved_blocks", ToJson(object.approved_blocks_));
  jo << ctie("signatures", ToJson(object.signatures_));
  jo << ctie("attempts", ToJson(object.attempts_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_blockSignature &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.blockSignature");
  jo << ctie("signature", ToJson(object.signature_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_sentBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.sentBlock");
  jo << ctie("src", ToJson(object.src_));
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("file_hash", ToJson(object.file_hash_));
  jo << ctie("collated_data_file_hash", ToJson(object.collated_data_file_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_sentBlockEmpty &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.sentBlockEmpty");
}
void to_json(JsonValueScope &jv, const ton_api::hashable_vote &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.vote");
  jo << ctie("block", ToJson(object.block_));
  jo << ctie("node", ToJson(object.node_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_blockCandidate &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.blockCandidate");
  jo << ctie("block", ToJson(object.block_));
  jo << ctie("approved", ToJson(object.approved_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_blockCandidateAttempt &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.blockCandidateAttempt");
  jo << ctie("block", ToJson(object.block_));
  jo << ctie("votes", ToJson(object.votes_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_cntVector &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.cntVector");
  jo << ctie("data", ToJson(object.data_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_cntSortedVector &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.cntSortedVector");
  jo << ctie("data", ToJson(object.data_));
}
void to_json(JsonValueScope &jv, const ton_api::hashable_validatorSession &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "hashable.validatorSession");
  jo << ctie("ts", ToJson(object.ts_));
  jo << ctie("old_rounds", ToJson(object.old_rounds_));
  jo << ctie("cur_round", ToJson(object.cur_round_));
}
void to_json(JsonValueScope &jv, const ton_api::TestObject &object) {
  ton_api::downcast_call(const_cast<ton_api::TestObject &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::testObject &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "testObject");
  jo << ctie("value", ToJson(object.value_));
  jo << ctie("o", ToJson(object.o_));
  jo << ctie("f", ToJson(object.f_));
}
void to_json(JsonValueScope &jv, const ton_api::testString &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "testString");
  jo << ctie("value", ToJson(object.value_));
}
void to_json(JsonValueScope &jv, const ton_api::testInt &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "testInt");
  jo << ctie("value", ToJson(object.value_));
}
void to_json(JsonValueScope &jv, const ton_api::testVectorBytes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "testVectorBytes");
  jo << ctie("value", ToJson(JsonVectorBytes(object.value_)));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_Address &object) {
  ton_api::downcast_call(const_cast<ton_api::adnl_Address &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::adnl_address_udp &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.address.udp");
  jo << ctie("ip", ToJson(object.ip_));
  jo << ctie("port", ToJson(object.port_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_address_udp6 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.address.udp6");
  jo << ctie("ip", ToJson(object.ip_));
  jo << ctie("port", ToJson(object.port_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_address_tcp &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.address.tcp");
  jo << ctie("ip", ToJson(object.ip_));
  jo << ctie("port", ToJson(object.port_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_address_tcp6 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.address.tcp6");
  jo << ctie("ip", ToJson(object.ip_));
  jo << ctie("port", ToJson(object.port_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_address_tunnel &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.address.tunnel");
  if (object.to_) {
    jo << ctie("to", ToJson(object.to_));
  }
  if (object.tunid_) {
    jo << ctie("tunid", ToJson(object.tunid_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::adnl_addressList &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.addressList");
  jo << ctie("addrs", ToJson(object.addrs_));
  jo << ctie("version", ToJson(object.version_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_Message &object) {
  ton_api::downcast_call(const_cast<ton_api::adnl_Message &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_packet &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.packet");
  jo << ctie("packet", ToJson(JsonBytes{object.packet_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_createChannel &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.createChannel");
  jo << ctie("key", ToJson(object.key_));
  jo << ctie("date", ToJson(object.date_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_confirmChannel &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.confirmChannel");
  jo << ctie("key", ToJson(object.key_));
  jo << ctie("peer_key", ToJson(object.peer_key_));
  jo << ctie("date", ToJson(object.date_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_custom &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.custom");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_nop &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.nop");
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_reinit &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.reinit");
  jo << ctie("date", ToJson(object.date_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_query &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.query");
  jo << ctie("query_id", ToJson(object.query_id_));
  jo << ctie("query", ToJson(JsonBytes{object.query_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_message_answer &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.message.answer");
  jo << ctie("query_id", ToJson(object.query_id_));
  jo << ctie("answer", ToJson(JsonBytes{object.answer_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_node &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.node");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  if (object.addr_list_) {
    jo << ctie("addr_list", ToJson(object.addr_list_));
  }
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_nodes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.nodes");
  jo << ctie("nodes", ToJson(object.nodes_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_packetContents &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.packetContents");
  jo << ctie("rand1", ToJson(JsonBytes{object.rand1_}));
  if (object.flags_) {
    jo << ctie("flags", ToJson(object.flags_));
  }
  if (object.from_) {
    jo << ctie("from", ToJson(object.from_));
  }
  if (object.from_short_) {
    jo << ctie("from_short", ToJson(object.from_short_));
  }
  if (object.message_) {
    jo << ctie("message", ToJson(object.message_));
  }
  jo << ctie("messages", ToJson(object.messages_));
  if (object.address_) {
    jo << ctie("address", ToJson(object.address_));
  }
  jo << ctie("seqno", ToJson(JsonInt64{object.seqno_}));
  jo << ctie("recv_addr_list_version", ToJson(object.recv_addr_list_version_));
  jo << ctie("confirm_seqno", ToJson(JsonInt64{object.confirm_seqno_}));
  jo << ctie("reinit_date", ToJson(object.reinit_date_));
  jo << ctie("dst_reinit_date", ToJson(object.dst_reinit_date_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
  jo << ctie("rand2", ToJson(JsonBytes{object.rand2_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_PacketHeader &object) {
  ton_api::downcast_call(const_cast<ton_api::adnl_PacketHeader &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::adnl_packetHeader_secp256k1 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.packetHeader.secp256k1");
  jo << ctie("dst", ToJson(object.dst_));
  jo << ctie("point", ToJson(object.point_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_packetHeader_unenc &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.packetHeader.unenc");
  jo << ctie("dst", ToJson(object.dst_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_packetHeader_channel &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.packetHeader.channel");
  jo << ctie("dst", ToJson(object.dst_));
  jo << ctie("hash", ToJson(object.hash_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_config_global &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.config.global");
  if (object.static_nodes_) {
    jo << ctie("static_nodes", ToJson(object.static_nodes_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::adnl_fileTransfer_Message &object) {
  ton_api::downcast_call(const_cast<ton_api::adnl_fileTransfer_Message &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::adnl_fileTransfer_request &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.fileTransfer.request");
  jo << ctie("hash", ToJson(object.hash_));
  jo << ctie("id", ToJson(object.id_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_fileTransfer_ack &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.fileTransfer.ack");
  jo << ctie("hash", ToJson(object.hash_));
  jo << ctie("id", ToJson(object.id_));
  jo << ctie("seqno", ToJson(object.seqno_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_fileTransfer_finish &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.fileTransfer.finish");
  jo << ctie("hash", ToJson(object.hash_));
  jo << ctie("id", ToJson(object.id_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_fileTransfer_data &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.fileTransfer.data");
  jo << ctie("hash", ToJson(object.hash_));
  jo << ctie("id", ToJson(object.id_));
  jo << ctie("seqno", ToJson(object.seqno_));
  if (object.fer_) {
    jo << ctie("fer", ToJson(object.fer_));
  }
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_Full &object) {
  ton_api::downcast_call(const_cast<ton_api::adnl_id_Full &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_ed25519 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.ed25519");
  jo << ctie("key", ToJson(object.key_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_aes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.aes");
  jo << ctie("key", ToJson(object.key_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_unenc &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.unenc");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_overlay &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.overlay");
  jo << ctie("name", ToJson(JsonBytes{object.name_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_Pk &object) {
  ton_api::downcast_call(const_cast<ton_api::adnl_id_Pk &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_pk_unenc &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.pk.unenc");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_pk_ed25519 &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.pk.ed25519");
  jo << ctie("key", ToJson(object.key_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_pk_aes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.pk.aes");
  jo << ctie("key", ToJson(object.key_));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_pk_overlay &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.pk.overlay");
  jo << ctie("name", ToJson(JsonBytes{object.name_}));
}
void to_json(JsonValueScope &jv, const ton_api::adnl_id_short &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "adnl.id.short");
  jo << ctie("id", ToJson(object.id_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block");
  jo << ctie("incarnation", ToJson(object.incarnation_));
  jo << ctie("src", ToJson(object.src_));
  jo << ctie("height", ToJson(object.height_));
  if (object.data_) {
    jo << ctie("data", ToJson(object.data_));
  }
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_BlockResult &object) {
  ton_api::downcast_call(const_cast<ton_api::catchain_BlockResult &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::catchain_blockNotFound &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.blockNotFound");
}
void to_json(JsonValueScope &jv, const ton_api::catchain_blockResult &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.blockResult");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::catchain_blocks &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.blocks");
  jo << ctie("blocks", ToJson(object.blocks_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_Difference &object) {
  ton_api::downcast_call(const_cast<ton_api::catchain_Difference &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::catchain_difference &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.difference");
  jo << ctie("sent_upto", ToJson(object.sent_upto_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_differenceFork &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.differenceFork");
  if (object.left_) {
    jo << ctie("left", ToJson(object.left_));
  }
  if (object.right_) {
    jo << ctie("right", ToJson(object.right_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::catchain_firstblock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.firstblock");
  jo << ctie("unique_hash", ToJson(object.unique_hash_));
  jo << ctie("nodes", ToJson(object.nodes_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_sent &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.sent");
  jo << ctie("cnt", ToJson(object.cnt_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_blockUpdate &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.blockUpdate");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_data &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block.data");
  if (object.prev_) {
    jo << ctie("prev", ToJson(object.prev_));
  }
  jo << ctie("deps", ToJson(object.deps_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_dep &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block.dep");
  jo << ctie("src", ToJson(object.src_));
  jo << ctie("height", ToJson(object.height_));
  jo << ctie("data_hash", ToJson(object.data_hash_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_id &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block.id");
  jo << ctie("incarnation", ToJson(object.incarnation_));
  jo << ctie("src", ToJson(object.src_));
  jo << ctie("height", ToJson(object.height_));
  jo << ctie("data_hash", ToJson(object.data_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_inner_Data &object) {
  ton_api::downcast_call(const_cast<ton_api::catchain_block_inner_Data &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_badBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block.data.badBlock");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_fork &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block.data.fork");
  if (object.left_) {
    jo << ctie("left", ToJson(object.left_));
  }
  if (object.right_) {
    jo << ctie("right", ToJson(object.right_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_nop &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block.data.nop");
}
void to_json(JsonValueScope &jv, const ton_api::catchain_block_data_vector &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.block.data.vector");
  jo << ctie("msgs", ToJson(JsonVectorBytes(object.msgs_)));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_config_global &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.config.global");
  jo << ctie("tag", ToJson(object.tag_));
  jo << ctie("nodes", ToJson(object.nodes_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.config.local");
  jo << ctie("tag", ToJson(object.tag_));
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::config_global &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "config.global");
  if (object.adnl_) {
    jo << ctie("adnl", ToJson(object.adnl_));
  }
  if (object.dht_) {
    jo << ctie("dht", ToJson(object.dht_));
  }
  jo << ctie("catchains", ToJson(object.catchains_));
  jo << ctie("dummy0", ToJson(object.dummy0_));
  jo << ctie("validators", ToJson(object.validators_));
  jo << ctie("liteclients", ToJson(object.liteclients_));
}
void to_json(JsonValueScope &jv, const ton_api::config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "config.local");
  jo << ctie("udp_ports", ToJson(object.udp_ports_));
  jo << ctie("tcp_ports", ToJson(object.tcp_ports_));
  jo << ctie("local_ids", ToJson(object.local_ids_));
  jo << ctie("dht", ToJson(object.dht_));
  jo << ctie("public_overlays", ToJson(object.public_overlays_));
  jo << ctie("catchains", ToJson(object.catchains_));
  jo << ctie("dummy0", ToJson(object.dummy0_));
  jo << ctie("validators", ToJson(object.validators_));
  jo << ctie("liteservers", ToJson(object.liteservers_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_key &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.key");
  jo << ctie("id", ToJson(object.id_));
  jo << ctie("name", ToJson(JsonBytes{object.name_}));
  jo << ctie("idx", ToJson(object.idx_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_keyDescription &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.keyDescription");
  if (object.key_) {
    jo << ctie("key", ToJson(object.key_));
  }
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  if (object.update_rule_) {
    jo << ctie("update_rule", ToJson(object.update_rule_));
  }
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::dht_message &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.message");
  if (object.node_) {
    jo << ctie("node", ToJson(object.node_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::dht_node &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.node");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  if (object.addr_list_) {
    jo << ctie("addr_list", ToJson(object.addr_list_));
  }
  jo << ctie("version", ToJson(object.version_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::dht_nodes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.nodes");
  jo << ctie("nodes", ToJson(object.nodes_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_pong &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.pong");
  jo << ctie("random_id", ToJson(JsonInt64{object.random_id_}));
}
void to_json(JsonValueScope &jv, const ton_api::dht_stored &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.stored");
}
void to_json(JsonValueScope &jv, const ton_api::dht_UpdateRule &object) {
  ton_api::downcast_call(const_cast<ton_api::dht_UpdateRule &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::dht_updateRule_signature &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.updateRule.signature");
}
void to_json(JsonValueScope &jv, const ton_api::dht_updateRule_anybody &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.updateRule.anybody");
}
void to_json(JsonValueScope &jv, const ton_api::dht_updateRule_nodes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.updateRule.nodes");
  jo << ctie("max_nodes", ToJson(object.max_nodes_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_updateRule_overlayNodes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.updateRule.overlayNodes");
  jo << ctie("max_nodes", ToJson(object.max_nodes_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_value &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.value");
  if (object.key_) {
    jo << ctie("key", ToJson(object.key_));
  }
  jo << ctie("value", ToJson(JsonBytes{object.value_}));
  jo << ctie("ttl", ToJson(object.ttl_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::dht_ValueResult &object) {
  ton_api::downcast_call(const_cast<ton_api::dht_ValueResult &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::dht_valueNotFound &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.valueNotFound");
  if (object.nodes_) {
    jo << ctie("nodes", ToJson(object.nodes_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::dht_valueFound &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.valueFound");
  if (object.value_) {
    jo << ctie("value", ToJson(object.value_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::dht_config_global &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.config.global");
  if (object.static_nodes_) {
    jo << ctie("static_nodes", ToJson(object.static_nodes_));
  }
  jo << ctie("k", ToJson(object.k_));
  jo << ctie("a", ToJson(object.a_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_config_Local &object) {
  ton_api::downcast_call(const_cast<ton_api::dht_config_Local &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::dht_config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.config.local");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::dht_config_random_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.config.random.local");
  jo << ctie("cnt", ToJson(object.cnt_));
  if (object.addr_list_) {
    jo << ctie("addr_list", ToJson(object.addr_list_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::dummydb_block &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dummydb.block");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("flags", ToJson(object.flags_));
  jo << ctie("prev", ToJson(object.prev_));
  jo << ctie("next", ToJson(object.next_));
  jo << ctie("lt", ToJson(JsonInt64{object.lt_}));
  jo << ctie("state", ToJson(object.state_));
  jo << ctie("state_file", ToJson(object.state_file_));
  jo << ctie("proof", ToJson(object.proof_));
  jo << ctie("proof_link", ToJson(object.proof_link_));
  jo << ctie("signatures", ToJson(object.signatures_));
}
void to_json(JsonValueScope &jv, const ton_api::dummydb_gcValidatorSessionList &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dummydb.gcValidatorSessionList");
  jo << ctie("list", ToJson(object.list_));
}
void to_json(JsonValueScope &jv, const ton_api::dummyworkchain0_config_global &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dummyworkchain0.config.global");
  jo << ctie("zero_state_hash", ToJson(object.zero_state_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::dummyworkchain0_config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dummyworkchain0.config.local");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::fer_Type &object) {
  ton_api::downcast_call(const_cast<ton_api::fer_Type &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::fer_raptorQ &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "fer.raptorQ");
  jo << ctie("symbol_size", ToJson(object.symbol_size_));
  jo << ctie("total_symbols", ToJson(object.total_symbols_));
  jo << ctie("total_size", ToJson(object.total_size_));
}
void to_json(JsonValueScope &jv, const ton_api::fer_simple &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "fer.simple");
  jo << ctie("symbol_size", ToJson(object.symbol_size_));
  jo << ctie("total_symbols", ToJson(object.total_symbols_));
  jo << ctie("total_size", ToJson(object.total_size_));
}
void to_json(JsonValueScope &jv, const ton_api::id_config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "id.config.local");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  if (object.addr_list_) {
    jo << ctie("addr_list", ToJson(object.addr_list_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_accountId &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.accountId");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("id", ToJson(object.id_));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_accountState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.accountState");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  if (object.shardblk_) {
    jo << ctie("shardblk", ToJson(object.shardblk_));
  }
  jo << ctie("shard_proof", ToJson(JsonBytes{object.shard_proof_}));
  jo << ctie("proof", ToJson(JsonBytes{object.proof_}));
  jo << ctie("state", ToJson(JsonBytes{object.state_}));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_blockData &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.blockData");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_blockState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.blockState");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("file_hash", ToJson(object.file_hash_));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_currentTime &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.currentTime");
  jo << ctie("now", ToJson(object.now_));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_error &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.error");
  jo << ctie("code", ToJson(object.code_));
  jo << ctie("message", ToJson(object.message_));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_masterchainInfo &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.masterchainInfo");
  if (object.last_) {
    jo << ctie("last", ToJson(object.last_));
  }
  jo << ctie("state_root_hash", ToJson(object.state_root_hash_));
  if (object.init_) {
    jo << ctie("init", ToJson(object.init_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_sendMsgStatus &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.sendMsgStatus");
  jo << ctie("status", ToJson(object.status_));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_debug_verbosity &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.debug.verbosity");
  jo << ctie("value", ToJson(object.value_));
}
void to_json(JsonValueScope &jv, const ton_api::liteclient_config_global &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteclient.config.global");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("ip", ToJson(object.ip_));
  jo << ctie("port", ToJson(object.port_));
}
void to_json(JsonValueScope &jv, const ton_api::liteserver_config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteserver.config.local");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("port", ToJson(object.port_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_Broadcast &object) {
  ton_api::downcast_call(const_cast<ton_api::overlay_Broadcast &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::overlay_fer_received &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.fer.received");
  jo << ctie("hash", ToJson(object.hash_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_fer_completed &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.fer.completed");
  jo << ctie("hash", ToJson(object.hash_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_unicast &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.unicast");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_broadcast &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.broadcast");
  if (object.src_) {
    jo << ctie("src", ToJson(object.src_));
  }
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
  jo << ctie("date", ToJson(object.date_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastFer &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.broadcastFer");
  if (object.src_) {
    jo << ctie("src", ToJson(object.src_));
  }
  jo << ctie("hash", ToJson(object.hash_));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
  jo << ctie("seqno", ToJson(object.seqno_));
  if (object.fer_) {
    jo << ctie("fer", ToJson(object.fer_));
  }
  jo << ctie("date", ToJson(object.date_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastFerShort &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.broadcastFerShort");
  jo << ctie("hash", ToJson(object.hash_));
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastNotFound &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.broadcastNotFound");
}
void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastList &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.broadcastList");
  jo << ctie("hashes", ToJson(object.hashes_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_message &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.message");
  jo << ctie("overlay", ToJson(object.overlay_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_node &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.node");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("overlay", ToJson(object.overlay_));
  jo << ctie("version", ToJson(object.version_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_nodes &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.nodes");
  jo << ctie("nodes", ToJson(object.nodes_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_broadcastFer_id &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.broadcastFer.id");
  jo << ctie("src", ToJson(object.src_));
  jo << ctie("type", ToJson(object.type_));
  jo << ctie("hash", ToJson(object.hash_));
  jo << ctie("date", ToJson(object.date_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_config_Local &object) {
  ton_api::downcast_call(const_cast<ton_api::overlay_config_Local &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::overlay_config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.config.local");
  jo << ctie("name", ToJson(JsonBytes{object.name_}));
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::overlay_config_random_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.config.random.local");
  jo << ctie("cnt", ToJson(object.cnt_));
  jo << ctie("name", ToJson(JsonBytes{object.name_}));
  if (object.addr_list_) {
    jo << ctie("addr_list", ToJson(object.addr_list_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::rldp_Message &object) {
  ton_api::downcast_call(const_cast<ton_api::rldp_Message &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::rldp_message &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "rldp.message");
  jo << ctie("id", ToJson(object.id_));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::rldp_query &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "rldp.query");
  jo << ctie("query_id", ToJson(object.query_id_));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::rldp_answer &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "rldp.answer");
  jo << ctie("query_id", ToJson(object.query_id_));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::rldp_MessagePart &object) {
  ton_api::downcast_call(const_cast<ton_api::rldp_MessagePart &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::rldp_messagePart &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "rldp.messagePart");
  jo << ctie("transfer_id", ToJson(object.transfer_id_));
  if (object.fer_type_) {
    jo << ctie("fer_type", ToJson(object.fer_type_));
  }
  jo << ctie("part", ToJson(object.part_));
  jo << ctie("total_size", ToJson(JsonInt64{object.total_size_}));
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::rldp_confirm &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "rldp.confirm");
  jo << ctie("transfer_id", ToJson(object.transfer_id_));
  jo << ctie("part", ToJson(object.part_));
  jo << ctie("seqno", ToJson(object.seqno_));
}
void to_json(JsonValueScope &jv, const ton_api::rldp_complete &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "rldp.complete");
  jo << ctie("transfer_id", ToJson(object.transfer_id_));
  jo << ctie("part", ToJson(object.part_));
}
void to_json(JsonValueScope &jv, const ton_api::tcp_pong &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tcp.pong");
  jo << ctie("random_id", ToJson(JsonInt64{object.random_id_}));
}
void to_json(JsonValueScope &jv, const ton_api::test0_proof &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.proof");
  if (object.link_) {
    jo << ctie("link", ToJson(object.link_));
  }
  jo << ctie("validator_set_ts", ToJson(object.validator_set_ts_));
  jo << ctie("validator_set_hash", ToJson(object.validator_set_hash_));
  if (object.signatures_) {
    jo << ctie("signatures", ToJson(object.signatures_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::test0_proofLink &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.proofLink");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("prev", ToJson(object.prev_));
  jo << ctie("state", ToJson(object.state_));
  jo << ctie("split", ToJson(object.split_));
}
void to_json(JsonValueScope &jv, const ton_api::test0_shardchain_block &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.shardchain.block");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("prev", ToJson(object.prev_));
  jo << ctie("split", ToJson(object.split_));
  jo << ctie("ts", ToJson(object.ts_));
  jo << ctie("state", ToJson(object.state_));
  jo << ctie("validator_set_ts", ToJson(object.validator_set_ts_));
  jo << ctie("validator_set_hash", ToJson(object.validator_set_hash_));
  jo << ctie("pad", ToJson(JsonBytes{object.pad_}));
  if (object.extra_) {
    jo << ctie("extra", ToJson(object.extra_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::test0_shardchain_state &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.shardchain.state");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("ts", ToJson(object.ts_));
  jo << ctie("split", ToJson(object.split_));
  if (object.extra_) {
    jo << ctie("extra", ToJson(object.extra_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::test_validatorSession_block &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test.validatorSession.block");
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("height", ToJson(JsonInt64{object.height_}));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::test0_blockSignatures &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.blockSignatures");
  jo << ctie("signatures", ToJson(object.signatures_));
}
void to_json(JsonValueScope &jv, const ton_api::test0_extMessage &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.extMessage");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::test0_MasterchainBlockExtra &object) {
  ton_api::downcast_call(const_cast<ton_api::test0_MasterchainBlockExtra &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::test0_masterchainBlockExtra_empty &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.masterchainBlockExtra.empty");
}
void to_json(JsonValueScope &jv, const ton_api::test0_masterchainBlockExtra_extra &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.masterchainBlockExtra.extra");
  jo << ctie("randseed", ToJson(object.randseed_));
  jo << ctie("rotate", ToJson(object.rotate_));
  jo << ctie("shards", ToJson(object.shards_));
}
void to_json(JsonValueScope &jv, const ton_api::test0_MasterchainStateExtra &object) {
  ton_api::downcast_call(const_cast<ton_api::test0_MasterchainStateExtra &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::test0_masterchainStateExtra_empty &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.masterchainStateExtra.empty");
}
void to_json(JsonValueScope &jv, const ton_api::test0_masterchainStateExtra_extra &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.masterchainStateExtra.extra");
  jo << ctie("validator_ts", ToJson(object.validator_ts_));
  jo << ctie("validator_randseed", ToJson(object.validator_randseed_));
  jo << ctie("next_randseed", ToJson(object.next_randseed_));
  jo << ctie("next_rotate_at", ToJson(object.next_rotate_at_));
  jo << ctie("prev_blocks", ToJson(object.prev_blocks_));
  jo << ctie("shards", ToJson(object.shards_));
  jo << ctie("pool", ToJson(object.pool_));
}
void to_json(JsonValueScope &jv, const ton_api::test0_topShardBlockDescription &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.topShardBlockDescription");
  if (object.block_id_) {
    jo << ctie("block_id", ToJson(object.block_id_));
  }
  jo << ctie("after_split", ToJson(object.after_split_));
  jo << ctie("after_merge", ToJson(object.after_merge_));
  jo << ctie("before_split", ToJson(object.before_split_));
  jo << ctie("validator_set_ts", ToJson(object.validator_set_ts_));
  jo << ctie("validator_set_hash", ToJson(object.validator_set_hash_));
  jo << ctie("signatures", ToJson(JsonBytes{object.signatures_}));
}
void to_json(JsonValueScope &jv, const ton_api::test0_validatorSessionId &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.validatorSessionId");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
  jo << ctie("shard_from", ToJson(JsonInt64{object.shard_from_}));
  jo << ctie("ts", ToJson(object.ts_));
}
void to_json(JsonValueScope &jv, const ton_api::test0_validatorSet &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.validatorSet");
  jo << ctie("ts", ToJson(object.ts_));
  jo << ctie("validators", ToJson(object.validators_));
}
void to_json(JsonValueScope &jv, const ton_api::test0_validatorSetItem &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.validatorSetItem");
  jo << ctie("id", ToJson(object.id_));
  jo << ctie("weight", ToJson(JsonInt64{object.weight_}));
}
void to_json(JsonValueScope &jv, const ton_api::test0_masterchain_shardInfo &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "test0.masterchain.shardInfo");
  if (object.last_block_) {
    jo << ctie("last_block", ToJson(object.last_block_));
  }
  jo << ctie("before_merge", ToJson(object.before_merge_));
  jo << ctie("before_split", ToJson(object.before_split_));
  jo << ctie("after_merge", ToJson(object.after_merge_));
  jo << ctie("after_split", ToJson(object.after_split_));
}
void to_json(JsonValueScope &jv, const ton_api::ton_blockId &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "ton.blockId");
  jo << ctie("root_cell_hash", ToJson(object.root_cell_hash_));
  jo << ctie("file_hash", ToJson(object.file_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_BlockDescription &object) {
  ton_api::downcast_call(const_cast<ton_api::tonNode_BlockDescription &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_blockDescriptionEmpty &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.blockDescriptionEmpty");
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_blockDescription &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.blockDescription");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_blockIdExt &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.blockIdExt");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
  jo << ctie("seqno", ToJson(object.seqno_));
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("file_hash", ToJson(object.file_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_blockSignature &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.blockSignature");
  jo << ctie("who", ToJson(object.who_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_Broadcast &object) {
  ton_api::downcast_call(const_cast<ton_api::tonNode_Broadcast &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_blockBroadcast &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.blockBroadcast");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  jo << ctie("validator_set_ts", ToJson(object.validator_set_ts_));
  jo << ctie("validator_set_hash", ToJson(object.validator_set_hash_));
  jo << ctie("signatures", ToJson(object.signatures_));
  if (object.masterchain_block_id_) {
    jo << ctie("masterchain_block_id", ToJson(object.masterchain_block_id_));
  }
  jo << ctie("proof", ToJson(JsonBytes{object.proof_}));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_ihrMessageBroadcast &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.ihrMessageBroadcast");
  if (object.message_) {
    jo << ctie("message", ToJson(object.message_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_externalMessageBroadcast &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.externalMessageBroadcast");
  if (object.message_) {
    jo << ctie("message", ToJson(object.message_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_newShardBlockBroadcast &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.newShardBlockBroadcast");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_data &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.data");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_externalMessage &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.externalMessage");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_ihrMessage &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.ihrMessage");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_newShardBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.newShardBlock");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_Prepared &object) {
  ton_api::downcast_call(const_cast<ton_api::tonNode_Prepared &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_prepared &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.prepared");
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_notFound &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.notFound");
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_PreparedProof &object) {
  ton_api::downcast_call(const_cast<ton_api::tonNode_PreparedProof &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedProofEmpty &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.preparedProofEmpty");
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedProof &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.preparedProof");
  if (object.masterchain_block_) {
    jo << ctie("masterchain_block", ToJson(object.masterchain_block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedProofLink &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.preparedProofLink");
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_PreparedState &object) {
  ton_api::downcast_call(const_cast<ton_api::tonNode_PreparedState &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_preparedState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.preparedState");
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_notFoundState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.notFoundState");
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_sessionId &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.sessionId");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
  jo << ctie("utime_from", ToJson(object.utime_from_));
  jo << ctie("utime_to", ToJson(object.utime_to_));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_shardPublicOverlayId &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.shardPublicOverlayId");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("shard", ToJson(JsonInt64{object.shard_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_zeroStateIdExt &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.zeroStateIdExt");
  jo << ctie("workchain", ToJson(object.workchain_));
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("file_hash", ToJson(object.file_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::validator_config_global &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validator.config.global");
  jo << ctie("zero_state_root_hash", ToJson(object.zero_state_root_hash_));
  jo << ctie("zero_state_file_hash", ToJson(object.zero_state_file_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::validator_config_local &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validator.config.local");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_blockUpdate &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.blockUpdate");
  jo << ctie("ts", ToJson(JsonInt64{object.ts_}));
  jo << ctie("actions", ToJson(object.actions_));
  jo << ctie("state", ToJson(object.state_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_candidate &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.candidate");
  jo << ctie("src", ToJson(object.src_));
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
  jo << ctie("collated_data", ToJson(JsonBytes{object.collated_data_}));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_candidateId &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.candidateId");
  jo << ctie("src", ToJson(object.src_));
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("file_hash", ToJson(object.file_hash_));
  jo << ctie("collated_data_file_hash", ToJson(object.collated_data_file_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_id &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.id");
  jo << ctie("slice", ToJson(object.slice_));
  jo << ctie("start_time", ToJson(object.start_time_));
  jo << ctie("end_time", ToJson(object.end_time_));
  jo << ctie("participants", ToJson(object.participants_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_Message &object) {
  ton_api::downcast_call(const_cast<ton_api::validatorSession_Message &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_startSession &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.startSession");
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_finishSession &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.finishSession");
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_pong &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.pong");
  jo << ctie("hash", ToJson(JsonInt64{object.hash_}));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_round_id &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.round.id");
  jo << ctie("session", ToJson(object.session_));
  jo << ctie("height", ToJson(JsonInt64{object.height_}));
  jo << ctie("prev_block", ToJson(object.prev_block_));
  jo << ctie("seqno", ToJson(object.seqno_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_round_Message &object) {
  ton_api::downcast_call(const_cast<ton_api::validatorSession_round_Message &>(object), [&jv](const auto &object) { to_json(jv, object); });
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_submittedBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.submittedBlock");
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("root_hash", ToJson(object.root_hash_));
  jo << ctie("file_hash", ToJson(object.file_hash_));
  jo << ctie("collated_data_file_hash", ToJson(object.collated_data_file_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_approvedBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.approvedBlock");
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("candidate", ToJson(object.candidate_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_commit &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.commit");
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("candidate", ToJson(object.candidate_));
  jo << ctie("signature", ToJson(JsonBytes{object.signature_}));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_vote &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.vote");
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("attempt", ToJson(object.attempt_));
  jo << ctie("candidate", ToJson(object.candidate_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_precommit &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.precommit");
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("attempt", ToJson(object.attempt_));
  jo << ctie("candidate", ToJson(object.candidate_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_message_empty &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.message.empty");
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("attempt", ToJson(object.attempt_));
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_candidate_id &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.candidate.id");
  jo << ctie("round", ToJson(object.round_));
  jo << ctie("block_hash", ToJson(object.block_hash_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_getBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.getBlock");
  jo << ctie("block", ToJson(object.block_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_getBlockHistory &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.getBlockHistory");
  jo << ctie("block", ToJson(object.block_));
  jo << ctie("height", ToJson(JsonInt64{object.height_}));
  jo << ctie("stop_if", ToJson(object.stop_if_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_getBlocks &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.getBlocks");
  jo << ctie("blocks", ToJson(object.blocks_));
}
void to_json(JsonValueScope &jv, const ton_api::catchain_getDifference &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "catchain.getDifference");
  jo << ctie("rt", ToJson(object.rt_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_findNode &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.findNode");
  jo << ctie("key", ToJson(object.key_));
  jo << ctie("k", ToJson(object.k_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_findValue &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.findValue");
  jo << ctie("key", ToJson(object.key_));
  jo << ctie("k", ToJson(object.k_));
}
void to_json(JsonValueScope &jv, const ton_api::dht_getSignedAddressList &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.getSignedAddressList");
}
void to_json(JsonValueScope &jv, const ton_api::dht_ping &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.ping");
  jo << ctie("random_id", ToJson(JsonInt64{object.random_id_}));
}
void to_json(JsonValueScope &jv, const ton_api::dht_query &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.query");
  if (object.node_) {
    jo << ctie("node", ToJson(object.node_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::dht_store &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "dht.store");
  if (object.value_) {
    jo << ctie("value", ToJson(object.value_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::getTestObject &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "getTestObject");
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_debug_setVerbosity &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.debug.setVerbosity");
  if (object.verbosity_) {
    jo << ctie("verbosity", ToJson(object.verbosity_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_getAccountState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.getAccountState");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
  if (object.account_) {
    jo << ctie("account", ToJson(object.account_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_getBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.getBlock");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_getMasterchainInfo &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.getMasterchainInfo");
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_getState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.getState");
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_getTime &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.getTime");
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_query &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.query");
  jo << ctie("data", ToJson(JsonBytes{object.data_}));
}
void to_json(JsonValueScope &jv, const ton_api::liteServer_sendMessage &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "liteServer.sendMessage");
  jo << ctie("body", ToJson(JsonBytes{object.body_}));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_getBroadcast &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.getBroadcast");
  jo << ctie("hash", ToJson(object.hash_));
}
void to_json(JsonValueScope &jv, const ton_api::overlay_getBroadcastList &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.getBroadcastList");
  if (object.list_) {
    jo << ctie("list", ToJson(object.list_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::overlay_getRandomPeers &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.getRandomPeers");
  if (object.peers_) {
    jo << ctie("peers", ToJson(object.peers_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::overlay_query &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "overlay.query");
  jo << ctie("overlay", ToJson(object.overlay_));
}
void to_json(JsonValueScope &jv, const ton_api::tcp_ping &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tcp.ping");
  jo << ctie("random_id", ToJson(JsonInt64{object.random_id_}));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.downloadBlock");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlockProof &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.downloadBlockProof");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadBlockProofLink &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.downloadBlockProofLink");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_downloadState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.downloadState");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_getNextBlockDescription &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.getNextBlockDescription");
  if (object.prev_block_) {
    jo << ctie("prev_block", ToJson(object.prev_block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareBlock &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.prepareBlock");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareBlockProof &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.prepareBlockProof");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
  jo << ctie("allow_partial", ToJson(object.allow_partial_));
}
void to_json(JsonValueScope &jv, const ton_api::tonNode_prepareState &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "tonNode.prepareState");
  if (object.block_) {
    jo << ctie("block", ToJson(object.block_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_downloadCandidate &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.downloadCandidate");
  jo << ctie("round", ToJson(object.round_));
  if (object.id_) {
    jo << ctie("id", ToJson(object.id_));
  }
}
void to_json(JsonValueScope &jv, const ton_api::validatorSession_ping &object) {
  auto jo = jv.enter_object();
  jo << ctie("@type", "validatorSession.ping");
  jo << ctie("hash", ToJson(JsonInt64{object.hash_}));
}
}  // namespace ton_api
}  // namespace ton
