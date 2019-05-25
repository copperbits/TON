#include "ton_api.h"

#include "tl/tl_object_parse.h"
#include "tl/tl_object_store.h"
#include "td/utils/int_types.h"

#include "td/utils/common.h"
#include "td/utils/format.h"
#include "td/utils/logging.h"
#include "td/utils/tl_parsers.h"
#include "td/utils/tl_storers.h"

namespace ton {
namespace ton_api {

std::string to_string(const BaseObject &value) {
  td::TlStorerToString storer;
  value.store(storer, "");
  return storer.str();
}

object_storage<Object> Object::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case hashable_bool::ID:
      return hashable_bool::fetch(p);
    case hashable_int32::ID:
      return hashable_int32::fetch(p);
    case hashable_int64::ID:
      return hashable_int64::fetch(p);
    case hashable_int256::ID:
      return hashable_int256::fetch(p);
    case hashable_bytes::ID:
      return hashable_bytes::fetch(p);
    case hashable_pair::ID:
      return hashable_pair::fetch(p);
    case hashable_vector::ID:
      return hashable_vector::fetch(p);
    case hashable_validatorSessionOldRound::ID:
      return hashable_validatorSessionOldRound::fetch(p);
    case hashable_validatorSessionRoundAttempt::ID:
      return hashable_validatorSessionRoundAttempt::fetch(p);
    case hashable_validatorSessionRound::ID:
      return hashable_validatorSessionRound::fetch(p);
    case hashable_blockSignature::ID:
      return hashable_blockSignature::fetch(p);
    case hashable_sentBlock::ID:
      return hashable_sentBlock::fetch(p);
    case hashable_sentBlockEmpty::ID:
      return hashable_sentBlockEmpty::fetch(p);
    case hashable_vote::ID:
      return hashable_vote::fetch(p);
    case hashable_blockCandidate::ID:
      return hashable_blockCandidate::fetch(p);
    case hashable_blockCandidateAttempt::ID:
      return hashable_blockCandidateAttempt::fetch(p);
    case hashable_cntVector::ID:
      return hashable_cntVector::fetch(p);
    case hashable_cntSortedVector::ID:
      return hashable_cntSortedVector::fetch(p);
    case hashable_validatorSession::ID:
      return hashable_validatorSession::fetch(p);
    case testObject::ID:
      return testObject::fetch(p);
    case testString::ID:
      return testString::fetch(p);
    case testInt::ID:
      return testInt::fetch(p);
    case testVectorBytes::ID:
      return testVectorBytes::fetch(p);
    case adnl_address_udp::ID:
      return adnl_address_udp::fetch(p);
    case adnl_address_udp6::ID:
      return adnl_address_udp6::fetch(p);
    case adnl_address_tcp::ID:
      return adnl_address_tcp::fetch(p);
    case adnl_address_tcp6::ID:
      return adnl_address_tcp6::fetch(p);
    case adnl_address_tunnel::ID:
      return adnl_address_tunnel::fetch(p);
    case adnl_addressList::ID:
      return adnl_addressList::fetch(p);
    case adnl_message_packet::ID:
      return adnl_message_packet::fetch(p);
    case adnl_message_createChannel::ID:
      return adnl_message_createChannel::fetch(p);
    case adnl_message_confirmChannel::ID:
      return adnl_message_confirmChannel::fetch(p);
    case adnl_message_custom::ID:
      return adnl_message_custom::fetch(p);
    case adnl_message_nop::ID:
      return adnl_message_nop::fetch(p);
    case adnl_message_reinit::ID:
      return adnl_message_reinit::fetch(p);
    case adnl_message_query::ID:
      return adnl_message_query::fetch(p);
    case adnl_message_answer::ID:
      return adnl_message_answer::fetch(p);
    case adnl_node::ID:
      return adnl_node::fetch(p);
    case adnl_nodes::ID:
      return adnl_nodes::fetch(p);
    case adnl_packetContents::ID:
      return adnl_packetContents::fetch(p);
    case adnl_packetHeader_secp256k1::ID:
      return adnl_packetHeader_secp256k1::fetch(p);
    case adnl_packetHeader_unenc::ID:
      return adnl_packetHeader_unenc::fetch(p);
    case adnl_packetHeader_channel::ID:
      return adnl_packetHeader_channel::fetch(p);
    case adnl_config_global::ID:
      return adnl_config_global::fetch(p);
    case adnl_fileTransfer_request::ID:
      return adnl_fileTransfer_request::fetch(p);
    case adnl_fileTransfer_ack::ID:
      return adnl_fileTransfer_ack::fetch(p);
    case adnl_fileTransfer_finish::ID:
      return adnl_fileTransfer_finish::fetch(p);
    case adnl_fileTransfer_data::ID:
      return adnl_fileTransfer_data::fetch(p);
    case adnl_id_ed25519::ID:
      return adnl_id_ed25519::fetch(p);
    case adnl_id_aes::ID:
      return adnl_id_aes::fetch(p);
    case adnl_id_unenc::ID:
      return adnl_id_unenc::fetch(p);
    case adnl_id_overlay::ID:
      return adnl_id_overlay::fetch(p);
    case adnl_id_pk_unenc::ID:
      return adnl_id_pk_unenc::fetch(p);
    case adnl_id_pk_ed25519::ID:
      return adnl_id_pk_ed25519::fetch(p);
    case adnl_id_pk_aes::ID:
      return adnl_id_pk_aes::fetch(p);
    case adnl_id_pk_overlay::ID:
      return adnl_id_pk_overlay::fetch(p);
    case adnl_id_short::ID:
      return adnl_id_short::fetch(p);
    case catchain_block::ID:
      return catchain_block::fetch(p);
    case catchain_blockNotFound::ID:
      return catchain_blockNotFound::fetch(p);
    case catchain_blockResult::ID:
      return catchain_blockResult::fetch(p);
    case catchain_blocks::ID:
      return catchain_blocks::fetch(p);
    case catchain_difference::ID:
      return catchain_difference::fetch(p);
    case catchain_differenceFork::ID:
      return catchain_differenceFork::fetch(p);
    case catchain_firstblock::ID:
      return catchain_firstblock::fetch(p);
    case catchain_sent::ID:
      return catchain_sent::fetch(p);
    case catchain_blockUpdate::ID:
      return catchain_blockUpdate::fetch(p);
    case catchain_block_data::ID:
      return catchain_block_data::fetch(p);
    case catchain_block_dep::ID:
      return catchain_block_dep::fetch(p);
    case catchain_block_id::ID:
      return catchain_block_id::fetch(p);
    case catchain_block_data_badBlock::ID:
      return catchain_block_data_badBlock::fetch(p);
    case catchain_block_data_fork::ID:
      return catchain_block_data_fork::fetch(p);
    case catchain_block_data_nop::ID:
      return catchain_block_data_nop::fetch(p);
    case catchain_block_data_vector::ID:
      return catchain_block_data_vector::fetch(p);
    case catchain_config_global::ID:
      return catchain_config_global::fetch(p);
    case catchain_config_local::ID:
      return catchain_config_local::fetch(p);
    case config_global::ID:
      return config_global::fetch(p);
    case config_local::ID:
      return config_local::fetch(p);
    case dht_key::ID:
      return dht_key::fetch(p);
    case dht_keyDescription::ID:
      return dht_keyDescription::fetch(p);
    case dht_message::ID:
      return dht_message::fetch(p);
    case dht_node::ID:
      return dht_node::fetch(p);
    case dht_nodes::ID:
      return dht_nodes::fetch(p);
    case dht_pong::ID:
      return dht_pong::fetch(p);
    case dht_stored::ID:
      return dht_stored::fetch(p);
    case dht_updateRule_signature::ID:
      return dht_updateRule_signature::fetch(p);
    case dht_updateRule_anybody::ID:
      return dht_updateRule_anybody::fetch(p);
    case dht_updateRule_nodes::ID:
      return dht_updateRule_nodes::fetch(p);
    case dht_updateRule_overlayNodes::ID:
      return dht_updateRule_overlayNodes::fetch(p);
    case dht_value::ID:
      return dht_value::fetch(p);
    case dht_valueNotFound::ID:
      return dht_valueNotFound::fetch(p);
    case dht_valueFound::ID:
      return dht_valueFound::fetch(p);
    case dht_config_global::ID:
      return dht_config_global::fetch(p);
    case dht_config_local::ID:
      return dht_config_local::fetch(p);
    case dht_config_random_local::ID:
      return dht_config_random_local::fetch(p);
    case dummydb_block::ID:
      return dummydb_block::fetch(p);
    case dummydb_gcValidatorSessionList::ID:
      return dummydb_gcValidatorSessionList::fetch(p);
    case dummyworkchain0_config_global::ID:
      return dummyworkchain0_config_global::fetch(p);
    case dummyworkchain0_config_local::ID:
      return dummyworkchain0_config_local::fetch(p);
    case fer_raptorQ::ID:
      return fer_raptorQ::fetch(p);
    case fer_simple::ID:
      return fer_simple::fetch(p);
    case id_config_local::ID:
      return id_config_local::fetch(p);
    case liteServer_accountId::ID:
      return liteServer_accountId::fetch(p);
    case liteServer_accountState::ID:
      return liteServer_accountState::fetch(p);
    case liteServer_blockData::ID:
      return liteServer_blockData::fetch(p);
    case liteServer_blockState::ID:
      return liteServer_blockState::fetch(p);
    case liteServer_currentTime::ID:
      return liteServer_currentTime::fetch(p);
    case liteServer_error::ID:
      return liteServer_error::fetch(p);
    case liteServer_masterchainInfo::ID:
      return liteServer_masterchainInfo::fetch(p);
    case liteServer_sendMsgStatus::ID:
      return liteServer_sendMsgStatus::fetch(p);
    case liteServer_debug_verbosity::ID:
      return liteServer_debug_verbosity::fetch(p);
    case liteclient_config_global::ID:
      return liteclient_config_global::fetch(p);
    case liteserver_config_local::ID:
      return liteserver_config_local::fetch(p);
    case overlay_fer_received::ID:
      return overlay_fer_received::fetch(p);
    case overlay_fer_completed::ID:
      return overlay_fer_completed::fetch(p);
    case overlay_unicast::ID:
      return overlay_unicast::fetch(p);
    case overlay_broadcast::ID:
      return overlay_broadcast::fetch(p);
    case overlay_broadcastFer::ID:
      return overlay_broadcastFer::fetch(p);
    case overlay_broadcastFerShort::ID:
      return overlay_broadcastFerShort::fetch(p);
    case overlay_broadcastNotFound::ID:
      return overlay_broadcastNotFound::fetch(p);
    case overlay_broadcastList::ID:
      return overlay_broadcastList::fetch(p);
    case overlay_message::ID:
      return overlay_message::fetch(p);
    case overlay_node::ID:
      return overlay_node::fetch(p);
    case overlay_nodes::ID:
      return overlay_nodes::fetch(p);
    case overlay_broadcastFer_id::ID:
      return overlay_broadcastFer_id::fetch(p);
    case overlay_config_local::ID:
      return overlay_config_local::fetch(p);
    case overlay_config_random_local::ID:
      return overlay_config_random_local::fetch(p);
    case rldp_message::ID:
      return rldp_message::fetch(p);
    case rldp_query::ID:
      return rldp_query::fetch(p);
    case rldp_answer::ID:
      return rldp_answer::fetch(p);
    case rldp_messagePart::ID:
      return rldp_messagePart::fetch(p);
    case rldp_confirm::ID:
      return rldp_confirm::fetch(p);
    case rldp_complete::ID:
      return rldp_complete::fetch(p);
    case tcp_pong::ID:
      return tcp_pong::fetch(p);
    case test0_proof::ID:
      return test0_proof::fetch(p);
    case test0_proofLink::ID:
      return test0_proofLink::fetch(p);
    case test0_shardchain_block::ID:
      return test0_shardchain_block::fetch(p);
    case test0_shardchain_state::ID:
      return test0_shardchain_state::fetch(p);
    case test_validatorSession_block::ID:
      return test_validatorSession_block::fetch(p);
    case test0_blockSignatures::ID:
      return test0_blockSignatures::fetch(p);
    case test0_extMessage::ID:
      return test0_extMessage::fetch(p);
    case test0_masterchainBlockExtra_empty::ID:
      return test0_masterchainBlockExtra_empty::fetch(p);
    case test0_masterchainBlockExtra_extra::ID:
      return test0_masterchainBlockExtra_extra::fetch(p);
    case test0_masterchainStateExtra_empty::ID:
      return test0_masterchainStateExtra_empty::fetch(p);
    case test0_masterchainStateExtra_extra::ID:
      return test0_masterchainStateExtra_extra::fetch(p);
    case test0_topShardBlockDescription::ID:
      return test0_topShardBlockDescription::fetch(p);
    case test0_validatorSessionId::ID:
      return test0_validatorSessionId::fetch(p);
    case test0_validatorSet::ID:
      return test0_validatorSet::fetch(p);
    case test0_validatorSetItem::ID:
      return test0_validatorSetItem::fetch(p);
    case test0_masterchain_shardInfo::ID:
      return test0_masterchain_shardInfo::fetch(p);
    case ton_blockId::ID:
      return ton_blockId::fetch(p);
    case tonNode_blockDescriptionEmpty::ID:
      return tonNode_blockDescriptionEmpty::fetch(p);
    case tonNode_blockDescription::ID:
      return tonNode_blockDescription::fetch(p);
    case tonNode_blockIdExt::ID:
      return tonNode_blockIdExt::fetch(p);
    case tonNode_blockSignature::ID:
      return tonNode_blockSignature::fetch(p);
    case tonNode_blockBroadcast::ID:
      return tonNode_blockBroadcast::fetch(p);
    case tonNode_ihrMessageBroadcast::ID:
      return tonNode_ihrMessageBroadcast::fetch(p);
    case tonNode_externalMessageBroadcast::ID:
      return tonNode_externalMessageBroadcast::fetch(p);
    case tonNode_newShardBlockBroadcast::ID:
      return tonNode_newShardBlockBroadcast::fetch(p);
    case tonNode_data::ID:
      return tonNode_data::fetch(p);
    case tonNode_externalMessage::ID:
      return tonNode_externalMessage::fetch(p);
    case tonNode_ihrMessage::ID:
      return tonNode_ihrMessage::fetch(p);
    case tonNode_newShardBlock::ID:
      return tonNode_newShardBlock::fetch(p);
    case tonNode_prepared::ID:
      return tonNode_prepared::fetch(p);
    case tonNode_notFound::ID:
      return tonNode_notFound::fetch(p);
    case tonNode_preparedProofEmpty::ID:
      return tonNode_preparedProofEmpty::fetch(p);
    case tonNode_preparedProof::ID:
      return tonNode_preparedProof::fetch(p);
    case tonNode_preparedProofLink::ID:
      return tonNode_preparedProofLink::fetch(p);
    case tonNode_preparedState::ID:
      return tonNode_preparedState::fetch(p);
    case tonNode_notFoundState::ID:
      return tonNode_notFoundState::fetch(p);
    case tonNode_sessionId::ID:
      return tonNode_sessionId::fetch(p);
    case tonNode_shardPublicOverlayId::ID:
      return tonNode_shardPublicOverlayId::fetch(p);
    case tonNode_zeroStateIdExt::ID:
      return tonNode_zeroStateIdExt::fetch(p);
    case validator_config_global::ID:
      return validator_config_global::fetch(p);
    case validator_config_local::ID:
      return validator_config_local::fetch(p);
    case validatorSession_blockUpdate::ID:
      return validatorSession_blockUpdate::fetch(p);
    case validatorSession_candidate::ID:
      return validatorSession_candidate::fetch(p);
    case validatorSession_candidateId::ID:
      return validatorSession_candidateId::fetch(p);
    case validatorSession_id::ID:
      return validatorSession_id::fetch(p);
    case validatorSession_message_startSession::ID:
      return validatorSession_message_startSession::fetch(p);
    case validatorSession_message_finishSession::ID:
      return validatorSession_message_finishSession::fetch(p);
    case validatorSession_pong::ID:
      return validatorSession_pong::fetch(p);
    case validatorSession_round_id::ID:
      return validatorSession_round_id::fetch(p);
    case validatorSession_message_submittedBlock::ID:
      return validatorSession_message_submittedBlock::fetch(p);
    case validatorSession_message_approvedBlock::ID:
      return validatorSession_message_approvedBlock::fetch(p);
    case validatorSession_message_commit::ID:
      return validatorSession_message_commit::fetch(p);
    case validatorSession_message_vote::ID:
      return validatorSession_message_vote::fetch(p);
    case validatorSession_message_precommit::ID:
      return validatorSession_message_precommit::fetch(p);
    case validatorSession_message_empty::ID:
      return validatorSession_message_empty::fetch(p);
    case validatorSession_candidate_id::ID:
      return validatorSession_candidate_id::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

object_storage<Function> Function::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case catchain_getBlock::ID:
      return catchain_getBlock::fetch(p);
    case catchain_getBlockHistory::ID:
      return catchain_getBlockHistory::fetch(p);
    case catchain_getBlocks::ID:
      return catchain_getBlocks::fetch(p);
    case catchain_getDifference::ID:
      return catchain_getDifference::fetch(p);
    case dht_findNode::ID:
      return dht_findNode::fetch(p);
    case dht_findValue::ID:
      return dht_findValue::fetch(p);
    case dht_getSignedAddressList::ID:
      return dht_getSignedAddressList::fetch(p);
    case dht_ping::ID:
      return dht_ping::fetch(p);
    case dht_query::ID:
      return dht_query::fetch(p);
    case dht_store::ID:
      return dht_store::fetch(p);
    case getTestObject::ID:
      return getTestObject::fetch(p);
    case liteServer_debug_setVerbosity::ID:
      return liteServer_debug_setVerbosity::fetch(p);
    case liteServer_getAccountState::ID:
      return liteServer_getAccountState::fetch(p);
    case liteServer_getBlock::ID:
      return liteServer_getBlock::fetch(p);
    case liteServer_getMasterchainInfo::ID:
      return liteServer_getMasterchainInfo::fetch(p);
    case liteServer_getState::ID:
      return liteServer_getState::fetch(p);
    case liteServer_getTime::ID:
      return liteServer_getTime::fetch(p);
    case liteServer_query::ID:
      return liteServer_query::fetch(p);
    case liteServer_sendMessage::ID:
      return liteServer_sendMessage::fetch(p);
    case overlay_getBroadcast::ID:
      return overlay_getBroadcast::fetch(p);
    case overlay_getBroadcastList::ID:
      return overlay_getBroadcastList::fetch(p);
    case overlay_getRandomPeers::ID:
      return overlay_getRandomPeers::fetch(p);
    case overlay_query::ID:
      return overlay_query::fetch(p);
    case tcp_ping::ID:
      return tcp_ping::fetch(p);
    case tonNode_downloadBlock::ID:
      return tonNode_downloadBlock::fetch(p);
    case tonNode_downloadBlockProof::ID:
      return tonNode_downloadBlockProof::fetch(p);
    case tonNode_downloadBlockProofLink::ID:
      return tonNode_downloadBlockProofLink::fetch(p);
    case tonNode_downloadState::ID:
      return tonNode_downloadState::fetch(p);
    case tonNode_getNextBlockDescription::ID:
      return tonNode_getNextBlockDescription::fetch(p);
    case tonNode_prepareBlock::ID:
      return tonNode_prepareBlock::fetch(p);
    case tonNode_prepareBlockProof::ID:
      return tonNode_prepareBlockProof::fetch(p);
    case tonNode_prepareState::ID:
      return tonNode_prepareState::fetch(p);
    case validatorSession_downloadCandidate::ID:
      return validatorSession_downloadCandidate::fetch(p);
    case validatorSession_ping::ID:
      return validatorSession_ping::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

object_storage<Hashable> Hashable::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case hashable_bool::ID:
      return hashable_bool::fetch(p);
    case hashable_int32::ID:
      return hashable_int32::fetch(p);
    case hashable_int64::ID:
      return hashable_int64::fetch(p);
    case hashable_int256::ID:
      return hashable_int256::fetch(p);
    case hashable_bytes::ID:
      return hashable_bytes::fetch(p);
    case hashable_pair::ID:
      return hashable_pair::fetch(p);
    case hashable_vector::ID:
      return hashable_vector::fetch(p);
    case hashable_validatorSessionOldRound::ID:
      return hashable_validatorSessionOldRound::fetch(p);
    case hashable_validatorSessionRoundAttempt::ID:
      return hashable_validatorSessionRoundAttempt::fetch(p);
    case hashable_validatorSessionRound::ID:
      return hashable_validatorSessionRound::fetch(p);
    case hashable_blockSignature::ID:
      return hashable_blockSignature::fetch(p);
    case hashable_sentBlock::ID:
      return hashable_sentBlock::fetch(p);
    case hashable_sentBlockEmpty::ID:
      return hashable_sentBlockEmpty::fetch(p);
    case hashable_vote::ID:
      return hashable_vote::fetch(p);
    case hashable_blockCandidate::ID:
      return hashable_blockCandidate::fetch(p);
    case hashable_blockCandidateAttempt::ID:
      return hashable_blockCandidateAttempt::fetch(p);
    case hashable_cntVector::ID:
      return hashable_cntVector::fetch(p);
    case hashable_cntSortedVector::ID:
      return hashable_cntSortedVector::fetch(p);
    case hashable_validatorSession::ID:
      return hashable_validatorSession::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

hashable_bool::hashable_bool()
  : value_()
{}

hashable_bool::hashable_bool(bool value_)
  : value_(value_)
{}

const std::int32_t hashable_bool::ID;

hashable_bool::hashable_bool(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchBool::parse(p))
#undef FAIL
{}

void hashable_bool::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBool::store(value_, s);
}

void hashable_bool::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBool::store(value_, s);
}

void hashable_bool::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_bool");
    s.store_field("value", value_);
    s.store_class_end();
  }
}

hashable_int32::hashable_int32()
  : value_()
{}

hashable_int32::hashable_int32(std::int32_t value_)
  : value_(value_)
{}

const std::int32_t hashable_int32::ID;

hashable_int32::hashable_int32(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_int32::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void hashable_int32::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void hashable_int32::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_int32");
    s.store_field("value", value_);
    s.store_class_end();
  }
}

hashable_int64::hashable_int64()
  : value_()
{}

hashable_int64::hashable_int64(std::int64_t value_)
  : value_(value_)
{}

const std::int32_t hashable_int64::ID;

hashable_int64::hashable_int64(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchLong::parse(p))
#undef FAIL
{}

void hashable_int64::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void hashable_int64::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void hashable_int64::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_int64");
    s.store_field("value", value_);
    s.store_class_end();
  }
}

hashable_int256::hashable_int256()
  : value_()
{}

hashable_int256::hashable_int256(td::UInt256 const &value_)
  : value_(value_)
{}

const std::int32_t hashable_int256::ID;

hashable_int256::hashable_int256(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchInt256::parse(p))
#undef FAIL
{}

void hashable_int256::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void hashable_int256::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void hashable_int256::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_int256");
    s.store_field("value", value_);
    s.store_class_end();
  }
}

hashable_bytes::hashable_bytes()
  : value_()
{}

hashable_bytes::hashable_bytes(td::BufferSlice &&value_)
  : value_(std::move(value_))
{}

const std::int32_t hashable_bytes::ID;

hashable_bytes::hashable_bytes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void hashable_bytes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(value_, s);
}

void hashable_bytes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(value_, s);
}

void hashable_bytes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_bytes");
    s.store_bytes_field("value", value_);
    s.store_class_end();
  }
}

hashable_pair::hashable_pair()
  : left_()
  , right_()
{}

hashable_pair::hashable_pair(std::int32_t left_, std::int32_t right_)
  : left_(left_)
  , right_(right_)
{}

const std::int32_t hashable_pair::ID;

hashable_pair::hashable_pair(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : left_(TlFetchInt::parse(p))
  , right_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_pair::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(left_, s);
  TlStoreBinary::store(right_, s);
}

void hashable_pair::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(left_, s);
  TlStoreBinary::store(right_, s);
}

void hashable_pair::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_pair");
    s.store_field("left", left_);
    s.store_field("right", right_);
    s.store_class_end();
  }
}

hashable_vector::hashable_vector()
  : value_()
{}

hashable_vector::hashable_vector(std::vector<std::int32_t> &&value_)
  : value_(std::move(value_))
{}

const std::int32_t hashable_vector::ID;

hashable_vector::hashable_vector(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchVector<TlFetchInt>::parse(p))
#undef FAIL
{}

void hashable_vector::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(value_, s);
}

void hashable_vector::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(value_, s);
}

void hashable_vector::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_vector");
    { const std::vector<std::int32_t> &v = value_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("value", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

hashable_validatorSessionOldRound::hashable_validatorSessionOldRound()
  : seqno_()
  , block_()
  , signatures_()
{}

hashable_validatorSessionOldRound::hashable_validatorSessionOldRound(std::int32_t seqno_, std::int32_t block_, std::int32_t signatures_)
  : seqno_(seqno_)
  , block_(block_)
  , signatures_(signatures_)
{}

const std::int32_t hashable_validatorSessionOldRound::ID;

hashable_validatorSessionOldRound::hashable_validatorSessionOldRound(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : seqno_(TlFetchInt::parse(p))
  , block_(TlFetchInt::parse(p))
  , signatures_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_validatorSessionOldRound::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(signatures_, s);
}

void hashable_validatorSessionOldRound::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(signatures_, s);
}

void hashable_validatorSessionOldRound::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_validatorSessionOldRound");
    s.store_field("seqno", seqno_);
    s.store_field("block", block_);
    s.store_field("signatures", signatures_);
    s.store_class_end();
  }
}

hashable_validatorSessionRoundAttempt::hashable_validatorSessionRoundAttempt()
  : seqno_()
  , votes_()
  , precommitted_()
{}

hashable_validatorSessionRoundAttempt::hashable_validatorSessionRoundAttempt(std::int32_t seqno_, std::int32_t votes_, std::int32_t precommitted_)
  : seqno_(seqno_)
  , votes_(votes_)
  , precommitted_(precommitted_)
{}

const std::int32_t hashable_validatorSessionRoundAttempt::ID;

hashable_validatorSessionRoundAttempt::hashable_validatorSessionRoundAttempt(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : seqno_(TlFetchInt::parse(p))
  , votes_(TlFetchInt::parse(p))
  , precommitted_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_validatorSessionRoundAttempt::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(votes_, s);
  TlStoreBinary::store(precommitted_, s);
}

void hashable_validatorSessionRoundAttempt::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(votes_, s);
  TlStoreBinary::store(precommitted_, s);
}

void hashable_validatorSessionRoundAttempt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_validatorSessionRoundAttempt");
    s.store_field("seqno", seqno_);
    s.store_field("votes", votes_);
    s.store_field("precommitted", precommitted_);
    s.store_class_end();
  }
}

hashable_validatorSessionRound::hashable_validatorSessionRound()
  : locked_round_()
  , locked_block_()
  , seqno_()
  , precommitted_()
  , approved_blocks_()
  , signatures_()
  , attempts_()
{}

hashable_validatorSessionRound::hashable_validatorSessionRound(std::int32_t locked_round_, std::int32_t locked_block_, std::int32_t seqno_, bool precommitted_, std::int32_t approved_blocks_, std::int32_t signatures_, std::int32_t attempts_)
  : locked_round_(locked_round_)
  , locked_block_(locked_block_)
  , seqno_(seqno_)
  , precommitted_(precommitted_)
  , approved_blocks_(approved_blocks_)
  , signatures_(signatures_)
  , attempts_(attempts_)
{}

const std::int32_t hashable_validatorSessionRound::ID;

hashable_validatorSessionRound::hashable_validatorSessionRound(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : locked_round_(TlFetchInt::parse(p))
  , locked_block_(TlFetchInt::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , precommitted_(TlFetchBool::parse(p))
  , approved_blocks_(TlFetchInt::parse(p))
  , signatures_(TlFetchInt::parse(p))
  , attempts_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_validatorSessionRound::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(locked_round_, s);
  TlStoreBinary::store(locked_block_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBool::store(precommitted_, s);
  TlStoreBinary::store(approved_blocks_, s);
  TlStoreBinary::store(signatures_, s);
  TlStoreBinary::store(attempts_, s);
}

void hashable_validatorSessionRound::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(locked_round_, s);
  TlStoreBinary::store(locked_block_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBool::store(precommitted_, s);
  TlStoreBinary::store(approved_blocks_, s);
  TlStoreBinary::store(signatures_, s);
  TlStoreBinary::store(attempts_, s);
}

void hashable_validatorSessionRound::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_validatorSessionRound");
    s.store_field("locked_round", locked_round_);
    s.store_field("locked_block", locked_block_);
    s.store_field("seqno", seqno_);
    s.store_field("precommitted", precommitted_);
    s.store_field("approved_blocks", approved_blocks_);
    s.store_field("signatures", signatures_);
    s.store_field("attempts", attempts_);
    s.store_class_end();
  }
}

hashable_blockSignature::hashable_blockSignature()
  : signature_()
{}

hashable_blockSignature::hashable_blockSignature(std::int32_t signature_)
  : signature_(signature_)
{}

const std::int32_t hashable_blockSignature::ID;

hashable_blockSignature::hashable_blockSignature(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : signature_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_blockSignature::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(signature_, s);
}

void hashable_blockSignature::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(signature_, s);
}

void hashable_blockSignature::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_blockSignature");
    s.store_field("signature", signature_);
    s.store_class_end();
  }
}

hashable_sentBlock::hashable_sentBlock()
  : src_()
  , root_hash_()
  , file_hash_()
  , collated_data_file_hash_()
{}

hashable_sentBlock::hashable_sentBlock(std::int32_t src_, std::int32_t root_hash_, std::int32_t file_hash_, std::int32_t collated_data_file_hash_)
  : src_(src_)
  , root_hash_(root_hash_)
  , file_hash_(file_hash_)
  , collated_data_file_hash_(collated_data_file_hash_)
{}

const std::int32_t hashable_sentBlock::ID;

hashable_sentBlock::hashable_sentBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : src_(TlFetchInt::parse(p))
  , root_hash_(TlFetchInt::parse(p))
  , file_hash_(TlFetchInt::parse(p))
  , collated_data_file_hash_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_sentBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreBinary::store(collated_data_file_hash_, s);
}

void hashable_sentBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreBinary::store(collated_data_file_hash_, s);
}

void hashable_sentBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_sentBlock");
    s.store_field("src", src_);
    s.store_field("root_hash", root_hash_);
    s.store_field("file_hash", file_hash_);
    s.store_field("collated_data_file_hash", collated_data_file_hash_);
    s.store_class_end();
  }
}

hashable_sentBlockEmpty::hashable_sentBlockEmpty() {
}

const std::int32_t hashable_sentBlockEmpty::ID;

hashable_sentBlockEmpty::hashable_sentBlockEmpty(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void hashable_sentBlockEmpty::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void hashable_sentBlockEmpty::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void hashable_sentBlockEmpty::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_sentBlockEmpty");
    s.store_class_end();
  }
}

hashable_vote::hashable_vote()
  : block_()
  , node_()
{}

hashable_vote::hashable_vote(std::int32_t block_, std::int32_t node_)
  : block_(block_)
  , node_(node_)
{}

const std::int32_t hashable_vote::ID;

hashable_vote::hashable_vote(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchInt::parse(p))
  , node_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_vote::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(node_, s);
}

void hashable_vote::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(node_, s);
}

void hashable_vote::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_vote");
    s.store_field("block", block_);
    s.store_field("node", node_);
    s.store_class_end();
  }
}

hashable_blockCandidate::hashable_blockCandidate()
  : block_()
  , approved_()
{}

hashable_blockCandidate::hashable_blockCandidate(std::int32_t block_, std::int32_t approved_)
  : block_(block_)
  , approved_(approved_)
{}

const std::int32_t hashable_blockCandidate::ID;

hashable_blockCandidate::hashable_blockCandidate(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchInt::parse(p))
  , approved_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_blockCandidate::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(approved_, s);
}

void hashable_blockCandidate::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(approved_, s);
}

void hashable_blockCandidate::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_blockCandidate");
    s.store_field("block", block_);
    s.store_field("approved", approved_);
    s.store_class_end();
  }
}

hashable_blockCandidateAttempt::hashable_blockCandidateAttempt()
  : block_()
  , votes_()
{}

hashable_blockCandidateAttempt::hashable_blockCandidateAttempt(std::int32_t block_, std::int32_t votes_)
  : block_(block_)
  , votes_(votes_)
{}

const std::int32_t hashable_blockCandidateAttempt::ID;

hashable_blockCandidateAttempt::hashable_blockCandidateAttempt(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchInt::parse(p))
  , votes_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_blockCandidateAttempt::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(votes_, s);
}

void hashable_blockCandidateAttempt::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(votes_, s);
}

void hashable_blockCandidateAttempt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_blockCandidateAttempt");
    s.store_field("block", block_);
    s.store_field("votes", votes_);
    s.store_class_end();
  }
}

hashable_cntVector::hashable_cntVector()
  : data_()
{}

hashable_cntVector::hashable_cntVector(std::int32_t data_)
  : data_(data_)
{}

const std::int32_t hashable_cntVector::ID;

hashable_cntVector::hashable_cntVector(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_cntVector::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(data_, s);
}

void hashable_cntVector::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(data_, s);
}

void hashable_cntVector::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_cntVector");
    s.store_field("data", data_);
    s.store_class_end();
  }
}

hashable_cntSortedVector::hashable_cntSortedVector()
  : data_()
{}

hashable_cntSortedVector::hashable_cntSortedVector(std::int32_t data_)
  : data_(data_)
{}

const std::int32_t hashable_cntSortedVector::ID;

hashable_cntSortedVector::hashable_cntSortedVector(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_cntSortedVector::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(data_, s);
}

void hashable_cntSortedVector::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(data_, s);
}

void hashable_cntSortedVector::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_cntSortedVector");
    s.store_field("data", data_);
    s.store_class_end();
  }
}

hashable_validatorSession::hashable_validatorSession()
  : ts_()
  , old_rounds_()
  , cur_round_()
{}

hashable_validatorSession::hashable_validatorSession(std::int32_t ts_, std::int32_t old_rounds_, std::int32_t cur_round_)
  : ts_(ts_)
  , old_rounds_(old_rounds_)
  , cur_round_(cur_round_)
{}

const std::int32_t hashable_validatorSession::ID;

hashable_validatorSession::hashable_validatorSession(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : ts_(TlFetchInt::parse(p))
  , old_rounds_(TlFetchInt::parse(p))
  , cur_round_(TlFetchInt::parse(p))
#undef FAIL
{}

void hashable_validatorSession::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ts_, s);
  TlStoreBinary::store(old_rounds_, s);
  TlStoreBinary::store(cur_round_, s);
}

void hashable_validatorSession::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ts_, s);
  TlStoreBinary::store(old_rounds_, s);
  TlStoreBinary::store(cur_round_, s);
}

void hashable_validatorSession::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "hashable_validatorSession");
    s.store_field("ts", ts_);
    s.store_field("old_rounds", old_rounds_);
    s.store_field("cur_round", cur_round_);
    s.store_class_end();
  }
}

object_storage<TestObject> TestObject::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case testObject::ID:
      return testObject::fetch(p);
    case testString::ID:
      return testString::fetch(p);
    case testInt::ID:
      return testInt::fetch(p);
    case testVectorBytes::ID:
      return testVectorBytes::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

testObject::testObject()
  : value_()
  , o_()
  , f_()
{}

testObject::testObject(std::int32_t value_, object_storage<Object> &&o_, object_storage<Function> &&f_)
  : value_(value_)
  , o_(std::move(o_))
  , f_(std::move(f_))
{}

const std::int32_t testObject::ID;

testObject::testObject(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchInt::parse(p))
  , o_(TlFetchObject<Object>::parse(p))
  , f_(TlFetchObject<Function>::parse(p))
#undef FAIL
{}

void testObject::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
  TlStoreObject::store(o_, s);
  TlStoreObject::store(f_, s);
}

void testObject::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
  TlStoreObject::store(o_, s);
  TlStoreObject::store(f_, s);
}

void testObject::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "testObject");
    s.store_field("value", value_);
    if (o_ == nullptr) { s.store_field("o", "null"); } else { o_->store(s, "o"); }
    if (f_ == nullptr) { s.store_field("f", "null"); } else { f_->store(s, "f"); }
    s.store_class_end();
  }
}

testString::testString()
  : value_()
{}

testString::testString(std::string const &value_)
  : value_(value_)
{}

const std::int32_t testString::ID;

testString::testString(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchString<std::string>::parse(p))
#undef FAIL
{}

void testString::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(value_, s);
}

void testString::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(value_, s);
}

void testString::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "testString");
    s.store_field("value", value_);
    s.store_class_end();
  }
}

testInt::testInt()
  : value_()
{}

testInt::testInt(std::int32_t value_)
  : value_(value_)
{}

const std::int32_t testInt::ID;

testInt::testInt(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchInt::parse(p))
#undef FAIL
{}

void testInt::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void testInt::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void testInt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "testInt");
    s.store_field("value", value_);
    s.store_class_end();
  }
}

testVectorBytes::testVectorBytes()
  : value_()
{}

testVectorBytes::testVectorBytes(std::vector<td::BufferSlice> &&value_)
  : value_(std::move(value_))
{}

const std::int32_t testVectorBytes::ID;

testVectorBytes::testVectorBytes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchVector<TlFetchBytes<td::BufferSlice>>::parse(p))
#undef FAIL
{}

void testVectorBytes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreString>::store(value_, s);
}

void testVectorBytes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreString>::store(value_, s);
}

void testVectorBytes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "testVectorBytes");
    { const std::vector<td::BufferSlice> &v = value_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("value", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_bytes_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

object_storage<adnl_Address> adnl_Address::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case adnl_address_udp::ID:
      return adnl_address_udp::fetch(p);
    case adnl_address_udp6::ID:
      return adnl_address_udp6::fetch(p);
    case adnl_address_tcp::ID:
      return adnl_address_tcp::fetch(p);
    case adnl_address_tcp6::ID:
      return adnl_address_tcp6::fetch(p);
    case adnl_address_tunnel::ID:
      return adnl_address_tunnel::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

adnl_address_udp::adnl_address_udp()
  : ip_()
  , port_()
{}

adnl_address_udp::adnl_address_udp(std::int32_t ip_, std::int32_t port_)
  : ip_(ip_)
  , port_(port_)
{}

const std::int32_t adnl_address_udp::ID;

adnl_address_udp::adnl_address_udp(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : ip_(TlFetchInt::parse(p))
  , port_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_address_udp::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_udp::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_udp::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_address_udp");
    s.store_field("ip", ip_);
    s.store_field("port", port_);
    s.store_class_end();
  }
}

adnl_address_udp6::adnl_address_udp6()
  : ip_()
  , port_()
{}

adnl_address_udp6::adnl_address_udp6(td::UInt128 const &ip_, std::int32_t port_)
  : ip_(ip_)
  , port_(port_)
{}

const std::int32_t adnl_address_udp6::ID;

adnl_address_udp6::adnl_address_udp6(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : ip_(TlFetchInt128::parse(p))
  , port_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_address_udp6::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_udp6::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_udp6::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_address_udp6");
    s.store_field("ip", ip_);
    s.store_field("port", port_);
    s.store_class_end();
  }
}

adnl_address_tcp::adnl_address_tcp()
  : ip_()
  , port_()
{}

adnl_address_tcp::adnl_address_tcp(std::int32_t ip_, std::int32_t port_)
  : ip_(ip_)
  , port_(port_)
{}

const std::int32_t adnl_address_tcp::ID;

adnl_address_tcp::adnl_address_tcp(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : ip_(TlFetchInt::parse(p))
  , port_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_address_tcp::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_tcp::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_tcp::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_address_tcp");
    s.store_field("ip", ip_);
    s.store_field("port", port_);
    s.store_class_end();
  }
}

adnl_address_tcp6::adnl_address_tcp6()
  : ip_()
  , port_()
{}

adnl_address_tcp6::adnl_address_tcp6(td::UInt128 const &ip_, std::int32_t port_)
  : ip_(ip_)
  , port_(port_)
{}

const std::int32_t adnl_address_tcp6::ID;

adnl_address_tcp6::adnl_address_tcp6(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : ip_(TlFetchInt128::parse(p))
  , port_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_address_tcp6::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_tcp6::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void adnl_address_tcp6::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_address_tcp6");
    s.store_field("ip", ip_);
    s.store_field("port", port_);
    s.store_class_end();
  }
}

adnl_address_tunnel::adnl_address_tunnel()
  : to_()
  , tunid_()
{}

adnl_address_tunnel::adnl_address_tunnel(object_storage<adnl_Address> &&to_, object_storage<adnl_id_Full> &&tunid_)
  : to_(std::move(to_))
  , tunid_(std::move(tunid_))
{}

const std::int32_t adnl_address_tunnel::ID;

adnl_address_tunnel::adnl_address_tunnel(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : to_(TlFetchObject<adnl_Address>::parse(p))
  , tunid_(TlFetchObject<adnl_id_Full>::parse(p))
#undef FAIL
{}

void adnl_address_tunnel::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(to_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(tunid_, s);
}

void adnl_address_tunnel::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(to_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(tunid_, s);
}

void adnl_address_tunnel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_address_tunnel");
    if (to_ == nullptr) { s.store_field("to", "null"); } else { to_->store(s, "to"); }
    if (tunid_ == nullptr) { s.store_field("tunid", "null"); } else { tunid_->store(s, "tunid"); }
    s.store_class_end();
  }
}

adnl_addressList::adnl_addressList()
  : addrs_()
  , version_()
{}

adnl_addressList::adnl_addressList(std::vector<object_storage<adnl_Address>> &&addrs_, std::int32_t version_)
  : addrs_(std::move(addrs_))
  , version_(version_)
{}

const std::int32_t adnl_addressList::ID;

adnl_addressList::adnl_addressList(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : addrs_(TlFetchVector<TlFetchObject<adnl_Address>>::parse(p))
  , version_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_addressList::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(addrs_, s);
  TlStoreBinary::store(version_, s);
}

void adnl_addressList::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(addrs_, s);
  TlStoreBinary::store(version_, s);
}

void adnl_addressList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_addressList");
    { const std::vector<object_storage<adnl_Address>> &v = addrs_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("addrs", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_field("version", version_);
    s.store_class_end();
  }
}

object_storage<adnl_Message> adnl_Message::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case adnl_message_packet::ID:
      return adnl_message_packet::fetch(p);
    case adnl_message_createChannel::ID:
      return adnl_message_createChannel::fetch(p);
    case adnl_message_confirmChannel::ID:
      return adnl_message_confirmChannel::fetch(p);
    case adnl_message_custom::ID:
      return adnl_message_custom::fetch(p);
    case adnl_message_nop::ID:
      return adnl_message_nop::fetch(p);
    case adnl_message_reinit::ID:
      return adnl_message_reinit::fetch(p);
    case adnl_message_query::ID:
      return adnl_message_query::fetch(p);
    case adnl_message_answer::ID:
      return adnl_message_answer::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

adnl_message_packet::adnl_message_packet()
  : packet_()
{}

adnl_message_packet::adnl_message_packet(td::BufferSlice &&packet_)
  : packet_(std::move(packet_))
{}

const std::int32_t adnl_message_packet::ID;

adnl_message_packet::adnl_message_packet(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : packet_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_message_packet::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(packet_, s);
}

void adnl_message_packet::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(packet_, s);
}

void adnl_message_packet::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_packet");
    s.store_bytes_field("packet", packet_);
    s.store_class_end();
  }
}

adnl_message_createChannel::adnl_message_createChannel()
  : key_()
  , date_()
{}

adnl_message_createChannel::adnl_message_createChannel(td::UInt256 const &key_, std::int32_t date_)
  : key_(key_)
  , date_(date_)
{}

const std::int32_t adnl_message_createChannel::ID;

adnl_message_createChannel::adnl_message_createChannel(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
  , date_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_message_createChannel::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(date_, s);
}

void adnl_message_createChannel::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(date_, s);
}

void adnl_message_createChannel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_createChannel");
    s.store_field("key", key_);
    s.store_field("date", date_);
    s.store_class_end();
  }
}

adnl_message_confirmChannel::adnl_message_confirmChannel()
  : key_()
  , peer_key_()
  , date_()
{}

adnl_message_confirmChannel::adnl_message_confirmChannel(td::UInt256 const &key_, td::UInt256 const &peer_key_, std::int32_t date_)
  : key_(key_)
  , peer_key_(peer_key_)
  , date_(date_)
{}

const std::int32_t adnl_message_confirmChannel::ID;

adnl_message_confirmChannel::adnl_message_confirmChannel(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
  , peer_key_(TlFetchInt256::parse(p))
  , date_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_message_confirmChannel::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(peer_key_, s);
  TlStoreBinary::store(date_, s);
}

void adnl_message_confirmChannel::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(peer_key_, s);
  TlStoreBinary::store(date_, s);
}

void adnl_message_confirmChannel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_confirmChannel");
    s.store_field("key", key_);
    s.store_field("peer_key", peer_key_);
    s.store_field("date", date_);
    s.store_class_end();
  }
}

adnl_message_custom::adnl_message_custom()
  : data_()
{}

adnl_message_custom::adnl_message_custom(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t adnl_message_custom::ID;

adnl_message_custom::adnl_message_custom(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_message_custom::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void adnl_message_custom::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void adnl_message_custom::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_custom");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

adnl_message_nop::adnl_message_nop() {
}

const std::int32_t adnl_message_nop::ID;

adnl_message_nop::adnl_message_nop(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void adnl_message_nop::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void adnl_message_nop::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void adnl_message_nop::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_nop");
    s.store_class_end();
  }
}

adnl_message_reinit::adnl_message_reinit()
  : date_()
{}

adnl_message_reinit::adnl_message_reinit(std::int32_t date_)
  : date_(date_)
{}

const std::int32_t adnl_message_reinit::ID;

adnl_message_reinit::adnl_message_reinit(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : date_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_message_reinit::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(date_, s);
}

void adnl_message_reinit::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(date_, s);
}

void adnl_message_reinit::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_reinit");
    s.store_field("date", date_);
    s.store_class_end();
  }
}

adnl_message_query::adnl_message_query()
  : query_id_()
  , query_()
{}

adnl_message_query::adnl_message_query(td::UInt256 const &query_id_, td::BufferSlice &&query_)
  : query_id_(query_id_)
  , query_(std::move(query_))
{}

const std::int32_t adnl_message_query::ID;

adnl_message_query::adnl_message_query(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : query_id_(TlFetchInt256::parse(p))
  , query_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_message_query::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(query_, s);
}

void adnl_message_query::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(query_, s);
}

void adnl_message_query::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_query");
    s.store_field("query_id", query_id_);
    s.store_bytes_field("query", query_);
    s.store_class_end();
  }
}

adnl_message_answer::adnl_message_answer()
  : query_id_()
  , answer_()
{}

adnl_message_answer::adnl_message_answer(td::UInt256 const &query_id_, td::BufferSlice &&answer_)
  : query_id_(query_id_)
  , answer_(std::move(answer_))
{}

const std::int32_t adnl_message_answer::ID;

adnl_message_answer::adnl_message_answer(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : query_id_(TlFetchInt256::parse(p))
  , answer_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_message_answer::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(answer_, s);
}

void adnl_message_answer::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(answer_, s);
}

void adnl_message_answer::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_message_answer");
    s.store_field("query_id", query_id_);
    s.store_bytes_field("answer", answer_);
    s.store_class_end();
  }
}

adnl_node::adnl_node()
  : id_()
  , addr_list_()
  , signature_()
{}

adnl_node::adnl_node(object_storage<adnl_id_Full> &&id_, object_storage<adnl_addressList> &&addr_list_, td::BufferSlice &&signature_)
  : id_(std::move(id_))
  , addr_list_(std::move(addr_list_))
  , signature_(std::move(signature_))
{}

const std::int32_t adnl_node::ID;

adnl_node::adnl_node(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_Full>::parse(p))
  , addr_list_(TlFetchObject<adnl_addressList>::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_node::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreObject::store(addr_list_, s);
  TlStoreString::store(signature_, s);
}

void adnl_node::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreObject::store(addr_list_, s);
  TlStoreString::store(signature_, s);
}

void adnl_node::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_node");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    if (addr_list_ == nullptr) { s.store_field("addr_list", "null"); } else { addr_list_->store(s, "addr_list"); }
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

adnl_nodes::adnl_nodes()
  : nodes_()
{}

adnl_nodes::adnl_nodes(std::vector<object_storage<adnl_node>> &&nodes_)
  : nodes_(std::move(nodes_))
{}

const std::int32_t adnl_nodes::ID;

adnl_nodes::adnl_nodes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : nodes_(TlFetchVector<TlFetchObject<adnl_node>>::parse(p))
#undef FAIL
{}

void adnl_nodes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(nodes_, s);
}

void adnl_nodes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(nodes_, s);
}

void adnl_nodes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_nodes");
    { const std::vector<object_storage<adnl_node>> &v = nodes_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("nodes", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

adnl_packetContents::adnl_packetContents()
  : rand1_()
  , flags_()
  , from_()
  , from_short_()
  , message_()
  , messages_()
  , address_()
  , seqno_()
  , recv_addr_list_version_()
  , confirm_seqno_()
  , reinit_date_()
  , dst_reinit_date_()
  , signature_()
  , rand2_()
{}

adnl_packetContents::adnl_packetContents(td::BufferSlice &&rand1_, std::int32_t flags_, object_storage<adnl_id_Full> &&from_, object_storage<adnl_id_short> &&from_short_, object_storage<adnl_Message> &&message_, std::vector<object_storage<adnl_Message>> &&messages_, object_storage<adnl_addressList> &&address_, std::int64_t seqno_, std::int32_t recv_addr_list_version_, std::int64_t confirm_seqno_, std::int32_t reinit_date_, std::int32_t dst_reinit_date_, td::BufferSlice &&signature_, td::BufferSlice &&rand2_)
  : rand1_(std::move(rand1_))
  , flags_(flags_)
  , from_(std::move(from_))
  , from_short_(std::move(from_short_))
  , message_(std::move(message_))
  , messages_(std::move(messages_))
  , address_(std::move(address_))
  , seqno_(seqno_)
  , recv_addr_list_version_(recv_addr_list_version_)
  , confirm_seqno_(confirm_seqno_)
  , reinit_date_(reinit_date_)
  , dst_reinit_date_(dst_reinit_date_)
  , signature_(std::move(signature_))
  , rand2_(std::move(rand2_))
{}

const std::int32_t adnl_packetContents::ID;

object_storage<adnl_packetContents> adnl_packetContents::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  object_storage<adnl_packetContents> res = create_tl_object<adnl_packetContents>();
  std::int32_t var0;
  res->rand1_ = TlFetchBytes<td::BufferSlice>::parse(p);
  if ((var0 = res->flags_ = TlFetchInt::parse(p)) < 0) { FAIL("Variable of type # can't be negative"); }
  if (var0 & 1) { res->from_ = TlFetchObject<adnl_id_Full>::parse(p); }
  if (var0 & 2) { res->from_short_ = TlFetchObject<adnl_id_short>::parse(p); }
  if (var0 & 4) { res->message_ = TlFetchObject<adnl_Message>::parse(p); }
  if (var0 & 8) { res->messages_ = TlFetchVector<TlFetchObject<adnl_Message>>::parse(p); }
  if (var0 & 64) { res->address_ = TlFetchObject<adnl_addressList>::parse(p); }
  if (var0 & 256) { res->seqno_ = TlFetchLong::parse(p); }
  if (var0 & 512) { res->recv_addr_list_version_ = TlFetchInt::parse(p); }
  if (var0 & 1024) { res->confirm_seqno_ = TlFetchLong::parse(p); }
  if (var0 & 2048) { res->reinit_date_ = TlFetchInt::parse(p); }
  if (var0 & 2048) { res->dst_reinit_date_ = TlFetchInt::parse(p); }
  if (var0 & 128) { res->signature_ = TlFetchBytes<td::BufferSlice>::parse(p); }
  res->rand2_ = TlFetchBytes<td::BufferSlice>::parse(p);
  if (p.get_error()) { FAIL(""); }
  return res;
#undef FAIL
}

void adnl_packetContents::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  std::int32_t var0;
  TlStoreString::store(rand1_, s);
  TlStoreBinary::store((var0 = flags_), s);
  if (var0 & 1) { TlStoreBoxedUnknown<TlStoreObject>::store(from_, s); }
  if (var0 & 2) { TlStoreObject::store(from_short_, s); }
  if (var0 & 4) { TlStoreBoxedUnknown<TlStoreObject>::store(message_, s); }
  if (var0 & 8) { TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(messages_, s); }
  if (var0 & 64) { TlStoreObject::store(address_, s); }
  if (var0 & 256) { TlStoreBinary::store(seqno_, s); }
  if (var0 & 512) { TlStoreBinary::store(recv_addr_list_version_, s); }
  if (var0 & 1024) { TlStoreBinary::store(confirm_seqno_, s); }
  if (var0 & 2048) { TlStoreBinary::store(reinit_date_, s); }
  if (var0 & 2048) { TlStoreBinary::store(dst_reinit_date_, s); }
  if (var0 & 128) { TlStoreString::store(signature_, s); }
  TlStoreString::store(rand2_, s);
}

void adnl_packetContents::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  std::int32_t var0;
  TlStoreString::store(rand1_, s);
  TlStoreBinary::store((var0 = flags_), s);
  if (var0 & 1) { TlStoreBoxedUnknown<TlStoreObject>::store(from_, s); }
  if (var0 & 2) { TlStoreObject::store(from_short_, s); }
  if (var0 & 4) { TlStoreBoxedUnknown<TlStoreObject>::store(message_, s); }
  if (var0 & 8) { TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(messages_, s); }
  if (var0 & 64) { TlStoreObject::store(address_, s); }
  if (var0 & 256) { TlStoreBinary::store(seqno_, s); }
  if (var0 & 512) { TlStoreBinary::store(recv_addr_list_version_, s); }
  if (var0 & 1024) { TlStoreBinary::store(confirm_seqno_, s); }
  if (var0 & 2048) { TlStoreBinary::store(reinit_date_, s); }
  if (var0 & 2048) { TlStoreBinary::store(dst_reinit_date_, s); }
  if (var0 & 128) { TlStoreString::store(signature_, s); }
  TlStoreString::store(rand2_, s);
}

void adnl_packetContents::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_packetContents");
  std::int32_t var0;
    s.store_bytes_field("rand1", rand1_);
    s.store_field("flags", (var0 = flags_));
    if (var0 & 1) { if (from_ == nullptr) { s.store_field("from", "null"); } else { from_->store(s, "from"); } }
    if (var0 & 2) { if (from_short_ == nullptr) { s.store_field("from_short", "null"); } else { from_short_->store(s, "from_short"); } }
    if (var0 & 4) { if (message_ == nullptr) { s.store_field("message", "null"); } else { message_->store(s, "message"); } }
    if (var0 & 8) { { const std::vector<object_storage<adnl_Message>> &v = messages_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("messages", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); } }
    if (var0 & 64) { if (address_ == nullptr) { s.store_field("address", "null"); } else { address_->store(s, "address"); } }
    if (var0 & 256) { s.store_field("seqno", seqno_); }
    if (var0 & 512) { s.store_field("recv_addr_list_version", recv_addr_list_version_); }
    if (var0 & 1024) { s.store_field("confirm_seqno", confirm_seqno_); }
    if (var0 & 2048) { s.store_field("reinit_date", reinit_date_); }
    if (var0 & 2048) { s.store_field("dst_reinit_date", dst_reinit_date_); }
    if (var0 & 128) { s.store_bytes_field("signature", signature_); }
    s.store_bytes_field("rand2", rand2_);
    s.store_class_end();
  }
}

object_storage<adnl_PacketHeader> adnl_PacketHeader::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case adnl_packetHeader_secp256k1::ID:
      return adnl_packetHeader_secp256k1::fetch(p);
    case adnl_packetHeader_unenc::ID:
      return adnl_packetHeader_unenc::fetch(p);
    case adnl_packetHeader_channel::ID:
      return adnl_packetHeader_channel::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

adnl_packetHeader_secp256k1::adnl_packetHeader_secp256k1()
  : dst_()
  , point_()
{}

adnl_packetHeader_secp256k1::adnl_packetHeader_secp256k1(td::UInt256 const &dst_, td::UInt256 const &point_)
  : dst_(dst_)
  , point_(point_)
{}

const std::int32_t adnl_packetHeader_secp256k1::ID;

adnl_packetHeader_secp256k1::adnl_packetHeader_secp256k1(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : dst_(TlFetchInt256::parse(p))
  , point_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_packetHeader_secp256k1::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(dst_, s);
  TlStoreBinary::store(point_, s);
}

void adnl_packetHeader_secp256k1::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(dst_, s);
  TlStoreBinary::store(point_, s);
}

void adnl_packetHeader_secp256k1::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_packetHeader_secp256k1");
    s.store_field("dst", dst_);
    s.store_field("point", point_);
    s.store_class_end();
  }
}

adnl_packetHeader_unenc::adnl_packetHeader_unenc()
  : dst_()
{}

adnl_packetHeader_unenc::adnl_packetHeader_unenc(td::UInt256 const &dst_)
  : dst_(dst_)
{}

const std::int32_t adnl_packetHeader_unenc::ID;

adnl_packetHeader_unenc::adnl_packetHeader_unenc(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : dst_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_packetHeader_unenc::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(dst_, s);
}

void adnl_packetHeader_unenc::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(dst_, s);
}

void adnl_packetHeader_unenc::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_packetHeader_unenc");
    s.store_field("dst", dst_);
    s.store_class_end();
  }
}

adnl_packetHeader_channel::adnl_packetHeader_channel()
  : dst_()
  , hash_()
{}

adnl_packetHeader_channel::adnl_packetHeader_channel(td::UInt256 const &dst_, td::UInt256 const &hash_)
  : dst_(dst_)
  , hash_(hash_)
{}

const std::int32_t adnl_packetHeader_channel::ID;

adnl_packetHeader_channel::adnl_packetHeader_channel(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : dst_(TlFetchInt256::parse(p))
  , hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_packetHeader_channel::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(dst_, s);
  TlStoreBinary::store(hash_, s);
}

void adnl_packetHeader_channel::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(dst_, s);
  TlStoreBinary::store(hash_, s);
}

void adnl_packetHeader_channel::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_packetHeader_channel");
    s.store_field("dst", dst_);
    s.store_field("hash", hash_);
    s.store_class_end();
  }
}

adnl_config_global::adnl_config_global()
  : static_nodes_()
{}

adnl_config_global::adnl_config_global(object_storage<adnl_nodes> &&static_nodes_)
  : static_nodes_(std::move(static_nodes_))
{}

const std::int32_t adnl_config_global::ID;

adnl_config_global::adnl_config_global(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : static_nodes_(TlFetchObject<adnl_nodes>::parse(p))
#undef FAIL
{}

void adnl_config_global::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(static_nodes_, s);
}

void adnl_config_global::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(static_nodes_, s);
}

void adnl_config_global::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_config_global");
    if (static_nodes_ == nullptr) { s.store_field("static_nodes", "null"); } else { static_nodes_->store(s, "static_nodes"); }
    s.store_class_end();
  }
}

object_storage<adnl_fileTransfer_Message> adnl_fileTransfer_Message::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case adnl_fileTransfer_request::ID:
      return adnl_fileTransfer_request::fetch(p);
    case adnl_fileTransfer_ack::ID:
      return adnl_fileTransfer_ack::fetch(p);
    case adnl_fileTransfer_finish::ID:
      return adnl_fileTransfer_finish::fetch(p);
    case adnl_fileTransfer_data::ID:
      return adnl_fileTransfer_data::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

adnl_fileTransfer_request::adnl_fileTransfer_request()
  : hash_()
  , id_()
{}

adnl_fileTransfer_request::adnl_fileTransfer_request(td::UInt256 const &hash_, td::UInt256 const &id_)
  : hash_(hash_)
  , id_(id_)
{}

const std::int32_t adnl_fileTransfer_request::ID;

adnl_fileTransfer_request::adnl_fileTransfer_request(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
  , id_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_fileTransfer_request::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
}

void adnl_fileTransfer_request::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
}

void adnl_fileTransfer_request::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_fileTransfer_request");
    s.store_field("hash", hash_);
    s.store_field("id", id_);
    s.store_class_end();
  }
}

adnl_fileTransfer_ack::adnl_fileTransfer_ack()
  : hash_()
  , id_()
  , seqno_()
{}

adnl_fileTransfer_ack::adnl_fileTransfer_ack(td::UInt256 const &hash_, td::UInt256 const &id_, std::int32_t seqno_)
  : hash_(hash_)
  , id_(id_)
  , seqno_(seqno_)
{}

const std::int32_t adnl_fileTransfer_ack::ID;

adnl_fileTransfer_ack::adnl_fileTransfer_ack(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
  , id_(TlFetchInt256::parse(p))
  , seqno_(TlFetchInt::parse(p))
#undef FAIL
{}

void adnl_fileTransfer_ack::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
  TlStoreBinary::store(seqno_, s);
}

void adnl_fileTransfer_ack::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
  TlStoreBinary::store(seqno_, s);
}

void adnl_fileTransfer_ack::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_fileTransfer_ack");
    s.store_field("hash", hash_);
    s.store_field("id", id_);
    s.store_field("seqno", seqno_);
    s.store_class_end();
  }
}

adnl_fileTransfer_finish::adnl_fileTransfer_finish()
  : hash_()
  , id_()
{}

adnl_fileTransfer_finish::adnl_fileTransfer_finish(td::UInt256 const &hash_, td::UInt256 const &id_)
  : hash_(hash_)
  , id_(id_)
{}

const std::int32_t adnl_fileTransfer_finish::ID;

adnl_fileTransfer_finish::adnl_fileTransfer_finish(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
  , id_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_fileTransfer_finish::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
}

void adnl_fileTransfer_finish::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
}

void adnl_fileTransfer_finish::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_fileTransfer_finish");
    s.store_field("hash", hash_);
    s.store_field("id", id_);
    s.store_class_end();
  }
}

adnl_fileTransfer_data::adnl_fileTransfer_data()
  : hash_()
  , id_()
  , seqno_()
  , fer_()
  , data_()
{}

adnl_fileTransfer_data::adnl_fileTransfer_data(td::UInt256 const &hash_, td::UInt256 const &id_, std::int32_t seqno_, object_storage<fer_Type> &&fer_, td::BufferSlice &&data_)
  : hash_(hash_)
  , id_(id_)
  , seqno_(seqno_)
  , fer_(std::move(fer_))
  , data_(std::move(data_))
{}

const std::int32_t adnl_fileTransfer_data::ID;

adnl_fileTransfer_data::adnl_fileTransfer_data(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
  , id_(TlFetchInt256::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , fer_(TlFetchObject<fer_Type>::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_fileTransfer_data::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(fer_, s);
  TlStoreString::store(data_, s);
}

void adnl_fileTransfer_data::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(id_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(fer_, s);
  TlStoreString::store(data_, s);
}

void adnl_fileTransfer_data::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_fileTransfer_data");
    s.store_field("hash", hash_);
    s.store_field("id", id_);
    s.store_field("seqno", seqno_);
    if (fer_ == nullptr) { s.store_field("fer", "null"); } else { fer_->store(s, "fer"); }
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

object_storage<adnl_id_Full> adnl_id_Full::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case adnl_id_ed25519::ID:
      return adnl_id_ed25519::fetch(p);
    case adnl_id_aes::ID:
      return adnl_id_aes::fetch(p);
    case adnl_id_unenc::ID:
      return adnl_id_unenc::fetch(p);
    case adnl_id_overlay::ID:
      return adnl_id_overlay::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

adnl_id_ed25519::adnl_id_ed25519()
  : key_()
{}

adnl_id_ed25519::adnl_id_ed25519(td::UInt256 const &key_)
  : key_(key_)
{}

const std::int32_t adnl_id_ed25519::ID;

adnl_id_ed25519::adnl_id_ed25519(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_id_ed25519::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_ed25519::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_ed25519::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_ed25519");
    s.store_field("key", key_);
    s.store_class_end();
  }
}

adnl_id_aes::adnl_id_aes()
  : key_()
{}

adnl_id_aes::adnl_id_aes(td::UInt256 const &key_)
  : key_(key_)
{}

const std::int32_t adnl_id_aes::ID;

adnl_id_aes::adnl_id_aes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_id_aes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_aes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_aes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_aes");
    s.store_field("key", key_);
    s.store_class_end();
  }
}

adnl_id_unenc::adnl_id_unenc()
  : data_()
{}

adnl_id_unenc::adnl_id_unenc(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t adnl_id_unenc::ID;

adnl_id_unenc::adnl_id_unenc(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_id_unenc::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void adnl_id_unenc::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void adnl_id_unenc::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_unenc");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

adnl_id_overlay::adnl_id_overlay()
  : name_()
{}

adnl_id_overlay::adnl_id_overlay(td::BufferSlice &&name_)
  : name_(std::move(name_))
{}

const std::int32_t adnl_id_overlay::ID;

adnl_id_overlay::adnl_id_overlay(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : name_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_id_overlay::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(name_, s);
}

void adnl_id_overlay::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(name_, s);
}

void adnl_id_overlay::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_overlay");
    s.store_bytes_field("name", name_);
    s.store_class_end();
  }
}

object_storage<adnl_id_Pk> adnl_id_Pk::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case adnl_id_pk_unenc::ID:
      return adnl_id_pk_unenc::fetch(p);
    case adnl_id_pk_ed25519::ID:
      return adnl_id_pk_ed25519::fetch(p);
    case adnl_id_pk_aes::ID:
      return adnl_id_pk_aes::fetch(p);
    case adnl_id_pk_overlay::ID:
      return adnl_id_pk_overlay::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

adnl_id_pk_unenc::adnl_id_pk_unenc()
  : data_()
{}

adnl_id_pk_unenc::adnl_id_pk_unenc(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t adnl_id_pk_unenc::ID;

adnl_id_pk_unenc::adnl_id_pk_unenc(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_id_pk_unenc::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void adnl_id_pk_unenc::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void adnl_id_pk_unenc::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_pk_unenc");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

adnl_id_pk_ed25519::adnl_id_pk_ed25519()
  : key_()
{}

adnl_id_pk_ed25519::adnl_id_pk_ed25519(td::UInt256 const &key_)
  : key_(key_)
{}

const std::int32_t adnl_id_pk_ed25519::ID;

adnl_id_pk_ed25519::adnl_id_pk_ed25519(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_id_pk_ed25519::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_pk_ed25519::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_pk_ed25519::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_pk_ed25519");
    s.store_field("key", key_);
    s.store_class_end();
  }
}

adnl_id_pk_aes::adnl_id_pk_aes()
  : key_()
{}

adnl_id_pk_aes::adnl_id_pk_aes(td::UInt256 const &key_)
  : key_(key_)
{}

const std::int32_t adnl_id_pk_aes::ID;

adnl_id_pk_aes::adnl_id_pk_aes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_id_pk_aes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_pk_aes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(key_, s);
}

void adnl_id_pk_aes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_pk_aes");
    s.store_field("key", key_);
    s.store_class_end();
  }
}

adnl_id_pk_overlay::adnl_id_pk_overlay()
  : name_()
{}

adnl_id_pk_overlay::adnl_id_pk_overlay(td::BufferSlice &&name_)
  : name_(std::move(name_))
{}

const std::int32_t adnl_id_pk_overlay::ID;

adnl_id_pk_overlay::adnl_id_pk_overlay(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : name_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void adnl_id_pk_overlay::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(name_, s);
}

void adnl_id_pk_overlay::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(name_, s);
}

void adnl_id_pk_overlay::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_pk_overlay");
    s.store_bytes_field("name", name_);
    s.store_class_end();
  }
}

adnl_id_short::adnl_id_short()
  : id_()
{}

adnl_id_short::adnl_id_short(td::UInt256 const &id_)
  : id_(id_)
{}

const std::int32_t adnl_id_short::ID;

adnl_id_short::adnl_id_short(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchInt256::parse(p))
#undef FAIL
{}

void adnl_id_short::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
}

void adnl_id_short::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
}

void adnl_id_short::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "adnl_id_short");
    s.store_field("id", id_);
    s.store_class_end();
  }
}

catchain_block::catchain_block()
  : incarnation_()
  , src_()
  , height_()
  , data_()
  , signature_()
{}

catchain_block::catchain_block(td::UInt256 const &incarnation_, std::int32_t src_, std::int32_t height_, object_storage<catchain_block_data> &&data_, td::BufferSlice &&signature_)
  : incarnation_(incarnation_)
  , src_(src_)
  , height_(height_)
  , data_(std::move(data_))
  , signature_(std::move(signature_))
{}

const std::int32_t catchain_block::ID;

catchain_block::catchain_block(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : incarnation_(TlFetchInt256::parse(p))
  , src_(TlFetchInt::parse(p))
  , height_(TlFetchInt::parse(p))
  , data_(TlFetchObject<catchain_block_data>::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void catchain_block::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(incarnation_, s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(height_, s);
  TlStoreObject::store(data_, s);
  TlStoreString::store(signature_, s);
}

void catchain_block::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(incarnation_, s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(height_, s);
  TlStoreObject::store(data_, s);
  TlStoreString::store(signature_, s);
}

void catchain_block::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block");
    s.store_field("incarnation", incarnation_);
    s.store_field("src", src_);
    s.store_field("height", height_);
    if (data_ == nullptr) { s.store_field("data", "null"); } else { data_->store(s, "data"); }
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

object_storage<catchain_BlockResult> catchain_BlockResult::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case catchain_blockNotFound::ID:
      return catchain_blockNotFound::fetch(p);
    case catchain_blockResult::ID:
      return catchain_blockResult::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

catchain_blockNotFound::catchain_blockNotFound() {
}

const std::int32_t catchain_blockNotFound::ID;

catchain_blockNotFound::catchain_blockNotFound(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void catchain_blockNotFound::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void catchain_blockNotFound::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void catchain_blockNotFound::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_blockNotFound");
    s.store_class_end();
  }
}

catchain_blockResult::catchain_blockResult()
  : block_()
{}

catchain_blockResult::catchain_blockResult(object_storage<catchain_block> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t catchain_blockResult::ID;

catchain_blockResult::catchain_blockResult(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<catchain_block>::parse(p))
#undef FAIL
{}

void catchain_blockResult::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void catchain_blockResult::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void catchain_blockResult::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_blockResult");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

catchain_blocks::catchain_blocks()
  : blocks_()
{}

catchain_blocks::catchain_blocks(std::vector<object_storage<catchain_block>> &&blocks_)
  : blocks_(std::move(blocks_))
{}

const std::int32_t catchain_blocks::ID;

catchain_blocks::catchain_blocks(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : blocks_(TlFetchVector<TlFetchObject<catchain_block>>::parse(p))
#undef FAIL
{}

void catchain_blocks::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(blocks_, s);
}

void catchain_blocks::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(blocks_, s);
}

void catchain_blocks::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_blocks");
    { const std::vector<object_storage<catchain_block>> &v = blocks_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("blocks", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

object_storage<catchain_Difference> catchain_Difference::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case catchain_difference::ID:
      return catchain_difference::fetch(p);
    case catchain_differenceFork::ID:
      return catchain_differenceFork::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

catchain_difference::catchain_difference()
  : sent_upto_()
{}

catchain_difference::catchain_difference(std::vector<std::int32_t> &&sent_upto_)
  : sent_upto_(std::move(sent_upto_))
{}

const std::int32_t catchain_difference::ID;

catchain_difference::catchain_difference(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : sent_upto_(TlFetchVector<TlFetchInt>::parse(p))
#undef FAIL
{}

void catchain_difference::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(sent_upto_, s);
}

void catchain_difference::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(sent_upto_, s);
}

void catchain_difference::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_difference");
    { const std::vector<std::int32_t> &v = sent_upto_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("sent_upto", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_differenceFork::catchain_differenceFork()
  : left_()
  , right_()
{}

catchain_differenceFork::catchain_differenceFork(object_storage<catchain_block_dep> &&left_, object_storage<catchain_block_dep> &&right_)
  : left_(std::move(left_))
  , right_(std::move(right_))
{}

const std::int32_t catchain_differenceFork::ID;

catchain_differenceFork::catchain_differenceFork(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : left_(TlFetchObject<catchain_block_dep>::parse(p))
  , right_(TlFetchObject<catchain_block_dep>::parse(p))
#undef FAIL
{}

void catchain_differenceFork::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(left_, s);
  TlStoreObject::store(right_, s);
}

void catchain_differenceFork::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(left_, s);
  TlStoreObject::store(right_, s);
}

void catchain_differenceFork::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_differenceFork");
    if (left_ == nullptr) { s.store_field("left", "null"); } else { left_->store(s, "left"); }
    if (right_ == nullptr) { s.store_field("right", "null"); } else { right_->store(s, "right"); }
    s.store_class_end();
  }
}

catchain_firstblock::catchain_firstblock()
  : unique_hash_()
  , nodes_()
{}

catchain_firstblock::catchain_firstblock(td::UInt256 const &unique_hash_, std::vector<td::UInt256> &&nodes_)
  : unique_hash_(unique_hash_)
  , nodes_(std::move(nodes_))
{}

const std::int32_t catchain_firstblock::ID;

catchain_firstblock::catchain_firstblock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : unique_hash_(TlFetchInt256::parse(p))
  , nodes_(TlFetchVector<TlFetchInt256>::parse(p))
#undef FAIL
{}

void catchain_firstblock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(unique_hash_, s);
  TlStoreVector<TlStoreBinary>::store(nodes_, s);
}

void catchain_firstblock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(unique_hash_, s);
  TlStoreVector<TlStoreBinary>::store(nodes_, s);
}

void catchain_firstblock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_firstblock");
    s.store_field("unique_hash", unique_hash_);
    { const std::vector<td::UInt256> &v = nodes_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("nodes", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_sent::catchain_sent()
  : cnt_()
{}

catchain_sent::catchain_sent(std::int32_t cnt_)
  : cnt_(cnt_)
{}

const std::int32_t catchain_sent::ID;

catchain_sent::catchain_sent(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : cnt_(TlFetchInt::parse(p))
#undef FAIL
{}

void catchain_sent::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(cnt_, s);
}

void catchain_sent::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(cnt_, s);
}

void catchain_sent::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_sent");
    s.store_field("cnt", cnt_);
    s.store_class_end();
  }
}

catchain_blockUpdate::catchain_blockUpdate()
  : block_()
{}

catchain_blockUpdate::catchain_blockUpdate(object_storage<catchain_block> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t catchain_blockUpdate::ID;

catchain_blockUpdate::catchain_blockUpdate(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<catchain_block>::parse(p))
#undef FAIL
{}

void catchain_blockUpdate::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void catchain_blockUpdate::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void catchain_blockUpdate::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_blockUpdate");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

catchain_block_data::catchain_block_data()
  : prev_()
  , deps_()
{}

catchain_block_data::catchain_block_data(object_storage<catchain_block_dep> &&prev_, std::vector<object_storage<catchain_block_dep>> &&deps_)
  : prev_(std::move(prev_))
  , deps_(std::move(deps_))
{}

const std::int32_t catchain_block_data::ID;

catchain_block_data::catchain_block_data(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : prev_(TlFetchObject<catchain_block_dep>::parse(p))
  , deps_(TlFetchVector<TlFetchObject<catchain_block_dep>>::parse(p))
#undef FAIL
{}

void catchain_block_data::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(prev_, s);
  TlStoreVector<TlStoreObject>::store(deps_, s);
}

void catchain_block_data::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(prev_, s);
  TlStoreVector<TlStoreObject>::store(deps_, s);
}

void catchain_block_data::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block_data");
    if (prev_ == nullptr) { s.store_field("prev", "null"); } else { prev_->store(s, "prev"); }
    { const std::vector<object_storage<catchain_block_dep>> &v = deps_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("deps", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_block_dep::catchain_block_dep()
  : src_()
  , height_()
  , data_hash_()
  , signature_()
{}

catchain_block_dep::catchain_block_dep(std::int32_t src_, std::int32_t height_, td::UInt256 const &data_hash_, td::BufferSlice &&signature_)
  : src_(src_)
  , height_(height_)
  , data_hash_(data_hash_)
  , signature_(std::move(signature_))
{}

const std::int32_t catchain_block_dep::ID;

catchain_block_dep::catchain_block_dep(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : src_(TlFetchInt::parse(p))
  , height_(TlFetchInt::parse(p))
  , data_hash_(TlFetchInt256::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void catchain_block_dep::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(height_, s);
  TlStoreBinary::store(data_hash_, s);
  TlStoreString::store(signature_, s);
}

void catchain_block_dep::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(height_, s);
  TlStoreBinary::store(data_hash_, s);
  TlStoreString::store(signature_, s);
}

void catchain_block_dep::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block_dep");
    s.store_field("src", src_);
    s.store_field("height", height_);
    s.store_field("data_hash", data_hash_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

catchain_block_id::catchain_block_id()
  : incarnation_()
  , src_()
  , height_()
  , data_hash_()
{}

catchain_block_id::catchain_block_id(td::UInt256 const &incarnation_, td::UInt256 const &src_, std::int32_t height_, td::UInt256 const &data_hash_)
  : incarnation_(incarnation_)
  , src_(src_)
  , height_(height_)
  , data_hash_(data_hash_)
{}

const std::int32_t catchain_block_id::ID;

catchain_block_id::catchain_block_id(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : incarnation_(TlFetchInt256::parse(p))
  , src_(TlFetchInt256::parse(p))
  , height_(TlFetchInt::parse(p))
  , data_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void catchain_block_id::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(incarnation_, s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(height_, s);
  TlStoreBinary::store(data_hash_, s);
}

void catchain_block_id::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(incarnation_, s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(height_, s);
  TlStoreBinary::store(data_hash_, s);
}

void catchain_block_id::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block_id");
    s.store_field("incarnation", incarnation_);
    s.store_field("src", src_);
    s.store_field("height", height_);
    s.store_field("data_hash", data_hash_);
    s.store_class_end();
  }
}

object_storage<catchain_block_inner_Data> catchain_block_inner_Data::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case catchain_block_data_badBlock::ID:
      return catchain_block_data_badBlock::fetch(p);
    case catchain_block_data_fork::ID:
      return catchain_block_data_fork::fetch(p);
    case catchain_block_data_nop::ID:
      return catchain_block_data_nop::fetch(p);
    case catchain_block_data_vector::ID:
      return catchain_block_data_vector::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

catchain_block_data_badBlock::catchain_block_data_badBlock()
  : block_()
{}

catchain_block_data_badBlock::catchain_block_data_badBlock(object_storage<catchain_block> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t catchain_block_data_badBlock::ID;

catchain_block_data_badBlock::catchain_block_data_badBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<catchain_block>::parse(p))
#undef FAIL
{}

void catchain_block_data_badBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void catchain_block_data_badBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void catchain_block_data_badBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block_data_badBlock");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

catchain_block_data_fork::catchain_block_data_fork()
  : left_()
  , right_()
{}

catchain_block_data_fork::catchain_block_data_fork(object_storage<catchain_block_dep> &&left_, object_storage<catchain_block_dep> &&right_)
  : left_(std::move(left_))
  , right_(std::move(right_))
{}

const std::int32_t catchain_block_data_fork::ID;

catchain_block_data_fork::catchain_block_data_fork(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : left_(TlFetchBoxed<TlFetchObject<catchain_block_dep>, 1511706959>::parse(p))
  , right_(TlFetchBoxed<TlFetchObject<catchain_block_dep>, 1511706959>::parse(p))
#undef FAIL
{}

void catchain_block_data_fork::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxed<TlStoreObject, 1511706959>::store(left_, s);
  TlStoreBoxed<TlStoreObject, 1511706959>::store(right_, s);
}

void catchain_block_data_fork::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxed<TlStoreObject, 1511706959>::store(left_, s);
  TlStoreBoxed<TlStoreObject, 1511706959>::store(right_, s);
}

void catchain_block_data_fork::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block_data_fork");
    if (left_ == nullptr) { s.store_field("left", "null"); } else { left_->store(s, "left"); }
    if (right_ == nullptr) { s.store_field("right", "null"); } else { right_->store(s, "right"); }
    s.store_class_end();
  }
}

catchain_block_data_nop::catchain_block_data_nop() {
}

const std::int32_t catchain_block_data_nop::ID;

catchain_block_data_nop::catchain_block_data_nop(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void catchain_block_data_nop::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void catchain_block_data_nop::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void catchain_block_data_nop::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block_data_nop");
    s.store_class_end();
  }
}

catchain_block_data_vector::catchain_block_data_vector()
  : msgs_()
{}

catchain_block_data_vector::catchain_block_data_vector(std::vector<td::BufferSlice> &&msgs_)
  : msgs_(std::move(msgs_))
{}

const std::int32_t catchain_block_data_vector::ID;

catchain_block_data_vector::catchain_block_data_vector(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : msgs_(TlFetchVector<TlFetchBytes<td::BufferSlice>>::parse(p))
#undef FAIL
{}

void catchain_block_data_vector::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreString>::store(msgs_, s);
}

void catchain_block_data_vector::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreString>::store(msgs_, s);
}

void catchain_block_data_vector::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_block_data_vector");
    { const std::vector<td::BufferSlice> &v = msgs_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("msgs", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_bytes_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_config_global::catchain_config_global()
  : tag_()
  , nodes_()
{}

catchain_config_global::catchain_config_global(td::UInt256 const &tag_, std::vector<object_storage<adnl_id_Full>> &&nodes_)
  : tag_(tag_)
  , nodes_(std::move(nodes_))
{}

const std::int32_t catchain_config_global::ID;

catchain_config_global::catchain_config_global(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : tag_(TlFetchInt256::parse(p))
  , nodes_(TlFetchVector<TlFetchObject<adnl_id_Full>>::parse(p))
#undef FAIL
{}

void catchain_config_global::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(tag_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(nodes_, s);
}

void catchain_config_global::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(tag_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(nodes_, s);
}

void catchain_config_global::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_config_global");
    s.store_field("tag", tag_);
    { const std::vector<object_storage<adnl_id_Full>> &v = nodes_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("nodes", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_config_local::catchain_config_local()
  : tag_()
  , id_()
{}

catchain_config_local::catchain_config_local(td::UInt256 const &tag_, object_storage<adnl_id_short> &&id_)
  : tag_(tag_)
  , id_(std::move(id_))
{}

const std::int32_t catchain_config_local::ID;

catchain_config_local::catchain_config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : tag_(TlFetchInt256::parse(p))
  , id_(TlFetchObject<adnl_id_short>::parse(p))
#undef FAIL
{}

void catchain_config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(tag_, s);
  TlStoreObject::store(id_, s);
}

void catchain_config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(tag_, s);
  TlStoreObject::store(id_, s);
}

void catchain_config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_config_local");
    s.store_field("tag", tag_);
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

config_global::config_global()
  : adnl_()
  , dht_()
  , catchains_()
  , dummy0_()
  , validators_()
  , liteclients_()
{}

config_global::config_global(object_storage<adnl_config_global> &&adnl_, object_storage<dht_config_global> &&dht_, std::vector<object_storage<catchain_config_global>> &&catchains_, std::vector<object_storage<dummyworkchain0_config_global>> &&dummy0_, std::vector<object_storage<validator_config_global>> &&validators_, std::vector<object_storage<liteclient_config_global>> &&liteclients_)
  : adnl_(std::move(adnl_))
  , dht_(std::move(dht_))
  , catchains_(std::move(catchains_))
  , dummy0_(std::move(dummy0_))
  , validators_(std::move(validators_))
  , liteclients_(std::move(liteclients_))
{}

const std::int32_t config_global::ID;

config_global::config_global(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : adnl_(TlFetchObject<adnl_config_global>::parse(p))
  , dht_(TlFetchObject<dht_config_global>::parse(p))
  , catchains_(TlFetchVector<TlFetchObject<catchain_config_global>>::parse(p))
  , dummy0_(TlFetchVector<TlFetchObject<dummyworkchain0_config_global>>::parse(p))
  , validators_(TlFetchVector<TlFetchObject<validator_config_global>>::parse(p))
  , liteclients_(TlFetchVector<TlFetchObject<liteclient_config_global>>::parse(p))
#undef FAIL
{}

void config_global::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(adnl_, s);
  TlStoreObject::store(dht_, s);
  TlStoreVector<TlStoreObject>::store(catchains_, s);
  TlStoreVector<TlStoreObject>::store(dummy0_, s);
  TlStoreVector<TlStoreObject>::store(validators_, s);
  TlStoreVector<TlStoreObject>::store(liteclients_, s);
}

void config_global::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(adnl_, s);
  TlStoreObject::store(dht_, s);
  TlStoreVector<TlStoreObject>::store(catchains_, s);
  TlStoreVector<TlStoreObject>::store(dummy0_, s);
  TlStoreVector<TlStoreObject>::store(validators_, s);
  TlStoreVector<TlStoreObject>::store(liteclients_, s);
}

void config_global::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "config_global");
    if (adnl_ == nullptr) { s.store_field("adnl", "null"); } else { adnl_->store(s, "adnl"); }
    if (dht_ == nullptr) { s.store_field("dht", "null"); } else { dht_->store(s, "dht"); }
    { const std::vector<object_storage<catchain_config_global>> &v = catchains_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("catchains", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<dummyworkchain0_config_global>> &v = dummy0_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("dummy0", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<validator_config_global>> &v = validators_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("validators", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<liteclient_config_global>> &v = liteclients_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("liteclients", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

config_local::config_local()
  : udp_ports_()
  , tcp_ports_()
  , local_ids_()
  , dht_()
  , public_overlays_()
  , catchains_()
  , dummy0_()
  , validators_()
  , liteservers_()
{}

config_local::config_local(std::vector<std::int32_t> &&udp_ports_, std::vector<std::int32_t> &&tcp_ports_, std::vector<object_storage<id_config_local>> &&local_ids_, std::vector<object_storage<dht_config_Local>> &&dht_, std::vector<object_storage<overlay_config_Local>> &&public_overlays_, std::vector<object_storage<catchain_config_local>> &&catchains_, std::vector<object_storage<dummyworkchain0_config_local>> &&dummy0_, std::vector<object_storage<validator_config_local>> &&validators_, std::vector<object_storage<liteserver_config_local>> &&liteservers_)
  : udp_ports_(std::move(udp_ports_))
  , tcp_ports_(std::move(tcp_ports_))
  , local_ids_(std::move(local_ids_))
  , dht_(std::move(dht_))
  , public_overlays_(std::move(public_overlays_))
  , catchains_(std::move(catchains_))
  , dummy0_(std::move(dummy0_))
  , validators_(std::move(validators_))
  , liteservers_(std::move(liteservers_))
{}

const std::int32_t config_local::ID;

config_local::config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : udp_ports_(TlFetchVector<TlFetchInt>::parse(p))
  , tcp_ports_(TlFetchVector<TlFetchInt>::parse(p))
  , local_ids_(TlFetchVector<TlFetchObject<id_config_local>>::parse(p))
  , dht_(TlFetchVector<TlFetchObject<dht_config_Local>>::parse(p))
  , public_overlays_(TlFetchVector<TlFetchObject<overlay_config_Local>>::parse(p))
  , catchains_(TlFetchVector<TlFetchObject<catchain_config_local>>::parse(p))
  , dummy0_(TlFetchVector<TlFetchObject<dummyworkchain0_config_local>>::parse(p))
  , validators_(TlFetchVector<TlFetchObject<validator_config_local>>::parse(p))
  , liteservers_(TlFetchVector<TlFetchObject<liteserver_config_local>>::parse(p))
#undef FAIL
{}

void config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(udp_ports_, s);
  TlStoreVector<TlStoreBinary>::store(tcp_ports_, s);
  TlStoreVector<TlStoreObject>::store(local_ids_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(dht_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(public_overlays_, s);
  TlStoreVector<TlStoreObject>::store(catchains_, s);
  TlStoreVector<TlStoreObject>::store(dummy0_, s);
  TlStoreVector<TlStoreObject>::store(validators_, s);
  TlStoreVector<TlStoreObject>::store(liteservers_, s);
}

void config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(udp_ports_, s);
  TlStoreVector<TlStoreBinary>::store(tcp_ports_, s);
  TlStoreVector<TlStoreObject>::store(local_ids_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(dht_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(public_overlays_, s);
  TlStoreVector<TlStoreObject>::store(catchains_, s);
  TlStoreVector<TlStoreObject>::store(dummy0_, s);
  TlStoreVector<TlStoreObject>::store(validators_, s);
  TlStoreVector<TlStoreObject>::store(liteservers_, s);
}

void config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "config_local");
    { const std::vector<std::int32_t> &v = udp_ports_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("udp_ports", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    { const std::vector<std::int32_t> &v = tcp_ports_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("tcp_ports", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    { const std::vector<object_storage<id_config_local>> &v = local_ids_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("local_ids", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<dht_config_Local>> &v = dht_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("dht", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<overlay_config_Local>> &v = public_overlays_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("public_overlays", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<catchain_config_local>> &v = catchains_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("catchains", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<dummyworkchain0_config_local>> &v = dummy0_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("dummy0", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<validator_config_local>> &v = validators_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("validators", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<liteserver_config_local>> &v = liteservers_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("liteservers", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

dht_key::dht_key()
  : id_()
  , name_()
  , idx_()
{}

dht_key::dht_key(td::UInt256 const &id_, td::BufferSlice &&name_, std::int32_t idx_)
  : id_(id_)
  , name_(std::move(name_))
  , idx_(idx_)
{}

const std::int32_t dht_key::ID;

dht_key::dht_key(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchInt256::parse(p))
  , name_(TlFetchBytes<td::BufferSlice>::parse(p))
  , idx_(TlFetchInt::parse(p))
#undef FAIL
{}

void dht_key::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
  TlStoreString::store(name_, s);
  TlStoreBinary::store(idx_, s);
}

void dht_key::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
  TlStoreString::store(name_, s);
  TlStoreBinary::store(idx_, s);
}

void dht_key::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_key");
    s.store_field("id", id_);
    s.store_bytes_field("name", name_);
    s.store_field("idx", idx_);
    s.store_class_end();
  }
}

dht_keyDescription::dht_keyDescription()
  : key_()
  , id_()
  , update_rule_()
  , signature_()
{}

dht_keyDescription::dht_keyDescription(object_storage<dht_key> &&key_, object_storage<adnl_id_Full> &&id_, object_storage<dht_UpdateRule> &&update_rule_, td::BufferSlice &&signature_)
  : key_(std::move(key_))
  , id_(std::move(id_))
  , update_rule_(std::move(update_rule_))
  , signature_(std::move(signature_))
{}

const std::int32_t dht_keyDescription::ID;

dht_keyDescription::dht_keyDescription(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchObject<dht_key>::parse(p))
  , id_(TlFetchObject<adnl_id_Full>::parse(p))
  , update_rule_(TlFetchObject<dht_UpdateRule>::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void dht_keyDescription::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(key_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(update_rule_, s);
  TlStoreString::store(signature_, s);
}

void dht_keyDescription::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(key_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(update_rule_, s);
  TlStoreString::store(signature_, s);
}

void dht_keyDescription::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_keyDescription");
    if (key_ == nullptr) { s.store_field("key", "null"); } else { key_->store(s, "key"); }
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    if (update_rule_ == nullptr) { s.store_field("update_rule", "null"); } else { update_rule_->store(s, "update_rule"); }
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

dht_message::dht_message()
  : node_()
{}

dht_message::dht_message(object_storage<dht_node> &&node_)
  : node_(std::move(node_))
{}

const std::int32_t dht_message::ID;

dht_message::dht_message(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : node_(TlFetchObject<dht_node>::parse(p))
#undef FAIL
{}

void dht_message::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(node_, s);
}

void dht_message::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(node_, s);
}

void dht_message::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_message");
    if (node_ == nullptr) { s.store_field("node", "null"); } else { node_->store(s, "node"); }
    s.store_class_end();
  }
}

dht_node::dht_node()
  : id_()
  , addr_list_()
  , version_()
  , signature_()
{}

dht_node::dht_node(object_storage<adnl_id_Full> &&id_, object_storage<adnl_addressList> &&addr_list_, std::int32_t version_, td::BufferSlice &&signature_)
  : id_(std::move(id_))
  , addr_list_(std::move(addr_list_))
  , version_(version_)
  , signature_(std::move(signature_))
{}

const std::int32_t dht_node::ID;

dht_node::dht_node(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_Full>::parse(p))
  , addr_list_(TlFetchObject<adnl_addressList>::parse(p))
  , version_(TlFetchInt::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void dht_node::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreObject::store(addr_list_, s);
  TlStoreBinary::store(version_, s);
  TlStoreString::store(signature_, s);
}

void dht_node::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreObject::store(addr_list_, s);
  TlStoreBinary::store(version_, s);
  TlStoreString::store(signature_, s);
}

void dht_node::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_node");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    if (addr_list_ == nullptr) { s.store_field("addr_list", "null"); } else { addr_list_->store(s, "addr_list"); }
    s.store_field("version", version_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

dht_nodes::dht_nodes()
  : nodes_()
{}

dht_nodes::dht_nodes(std::vector<object_storage<dht_node>> &&nodes_)
  : nodes_(std::move(nodes_))
{}

const std::int32_t dht_nodes::ID;

dht_nodes::dht_nodes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : nodes_(TlFetchVector<TlFetchObject<dht_node>>::parse(p))
#undef FAIL
{}

void dht_nodes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(nodes_, s);
}

void dht_nodes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(nodes_, s);
}

void dht_nodes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_nodes");
    { const std::vector<object_storage<dht_node>> &v = nodes_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("nodes", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

dht_pong::dht_pong()
  : random_id_()
{}

dht_pong::dht_pong(std::int64_t random_id_)
  : random_id_(random_id_)
{}

const std::int32_t dht_pong::ID;

dht_pong::dht_pong(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : random_id_(TlFetchLong::parse(p))
#undef FAIL
{}

void dht_pong::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(random_id_, s);
}

void dht_pong::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(random_id_, s);
}

void dht_pong::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_pong");
    s.store_field("random_id", random_id_);
    s.store_class_end();
  }
}

dht_stored::dht_stored() {
}

const std::int32_t dht_stored::ID;

dht_stored::dht_stored(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void dht_stored::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void dht_stored::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void dht_stored::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_stored");
    s.store_class_end();
  }
}

object_storage<dht_UpdateRule> dht_UpdateRule::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case dht_updateRule_signature::ID:
      return dht_updateRule_signature::fetch(p);
    case dht_updateRule_anybody::ID:
      return dht_updateRule_anybody::fetch(p);
    case dht_updateRule_nodes::ID:
      return dht_updateRule_nodes::fetch(p);
    case dht_updateRule_overlayNodes::ID:
      return dht_updateRule_overlayNodes::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

dht_updateRule_signature::dht_updateRule_signature() {
}

const std::int32_t dht_updateRule_signature::ID;

dht_updateRule_signature::dht_updateRule_signature(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void dht_updateRule_signature::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void dht_updateRule_signature::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void dht_updateRule_signature::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_updateRule_signature");
    s.store_class_end();
  }
}

dht_updateRule_anybody::dht_updateRule_anybody() {
}

const std::int32_t dht_updateRule_anybody::ID;

dht_updateRule_anybody::dht_updateRule_anybody(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void dht_updateRule_anybody::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void dht_updateRule_anybody::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void dht_updateRule_anybody::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_updateRule_anybody");
    s.store_class_end();
  }
}

dht_updateRule_nodes::dht_updateRule_nodes()
  : max_nodes_()
{}

dht_updateRule_nodes::dht_updateRule_nodes(std::int32_t max_nodes_)
  : max_nodes_(max_nodes_)
{}

const std::int32_t dht_updateRule_nodes::ID;

dht_updateRule_nodes::dht_updateRule_nodes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : max_nodes_(TlFetchInt::parse(p))
#undef FAIL
{}

void dht_updateRule_nodes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(max_nodes_, s);
}

void dht_updateRule_nodes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(max_nodes_, s);
}

void dht_updateRule_nodes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_updateRule_nodes");
    s.store_field("max_nodes", max_nodes_);
    s.store_class_end();
  }
}

dht_updateRule_overlayNodes::dht_updateRule_overlayNodes()
  : max_nodes_()
{}

dht_updateRule_overlayNodes::dht_updateRule_overlayNodes(std::int32_t max_nodes_)
  : max_nodes_(max_nodes_)
{}

const std::int32_t dht_updateRule_overlayNodes::ID;

dht_updateRule_overlayNodes::dht_updateRule_overlayNodes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : max_nodes_(TlFetchInt::parse(p))
#undef FAIL
{}

void dht_updateRule_overlayNodes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(max_nodes_, s);
}

void dht_updateRule_overlayNodes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(max_nodes_, s);
}

void dht_updateRule_overlayNodes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_updateRule_overlayNodes");
    s.store_field("max_nodes", max_nodes_);
    s.store_class_end();
  }
}

dht_value::dht_value()
  : key_()
  , value_()
  , ttl_()
  , signature_()
{}

dht_value::dht_value(object_storage<dht_keyDescription> &&key_, td::BufferSlice &&value_, std::int32_t ttl_, td::BufferSlice &&signature_)
  : key_(std::move(key_))
  , value_(std::move(value_))
  , ttl_(ttl_)
  , signature_(std::move(signature_))
{}

const std::int32_t dht_value::ID;

dht_value::dht_value(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchObject<dht_keyDescription>::parse(p))
  , value_(TlFetchBytes<td::BufferSlice>::parse(p))
  , ttl_(TlFetchInt::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void dht_value::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(key_, s);
  TlStoreString::store(value_, s);
  TlStoreBinary::store(ttl_, s);
  TlStoreString::store(signature_, s);
}

void dht_value::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(key_, s);
  TlStoreString::store(value_, s);
  TlStoreBinary::store(ttl_, s);
  TlStoreString::store(signature_, s);
}

void dht_value::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_value");
    if (key_ == nullptr) { s.store_field("key", "null"); } else { key_->store(s, "key"); }
    s.store_bytes_field("value", value_);
    s.store_field("ttl", ttl_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

object_storage<dht_ValueResult> dht_ValueResult::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case dht_valueNotFound::ID:
      return dht_valueNotFound::fetch(p);
    case dht_valueFound::ID:
      return dht_valueFound::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

dht_valueNotFound::dht_valueNotFound()
  : nodes_()
{}

dht_valueNotFound::dht_valueNotFound(object_storage<dht_nodes> &&nodes_)
  : nodes_(std::move(nodes_))
{}

const std::int32_t dht_valueNotFound::ID;

dht_valueNotFound::dht_valueNotFound(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : nodes_(TlFetchObject<dht_nodes>::parse(p))
#undef FAIL
{}

void dht_valueNotFound::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(nodes_, s);
}

void dht_valueNotFound::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(nodes_, s);
}

void dht_valueNotFound::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_valueNotFound");
    if (nodes_ == nullptr) { s.store_field("nodes", "null"); } else { nodes_->store(s, "nodes"); }
    s.store_class_end();
  }
}

dht_valueFound::dht_valueFound()
  : value_()
{}

dht_valueFound::dht_valueFound(object_storage<dht_value> &&value_)
  : value_(std::move(value_))
{}

const std::int32_t dht_valueFound::ID;

dht_valueFound::dht_valueFound(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchBoxed<TlFetchObject<dht_value>, -1867700277>::parse(p))
#undef FAIL
{}

void dht_valueFound::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxed<TlStoreObject, -1867700277>::store(value_, s);
}

void dht_valueFound::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxed<TlStoreObject, -1867700277>::store(value_, s);
}

void dht_valueFound::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_valueFound");
    if (value_ == nullptr) { s.store_field("value", "null"); } else { value_->store(s, "value"); }
    s.store_class_end();
  }
}

dht_config_global::dht_config_global()
  : static_nodes_()
  , k_()
  , a_()
{}

dht_config_global::dht_config_global(object_storage<dht_nodes> &&static_nodes_, std::int32_t k_, std::int32_t a_)
  : static_nodes_(std::move(static_nodes_))
  , k_(k_)
  , a_(a_)
{}

const std::int32_t dht_config_global::ID;

dht_config_global::dht_config_global(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : static_nodes_(TlFetchObject<dht_nodes>::parse(p))
  , k_(TlFetchInt::parse(p))
  , a_(TlFetchInt::parse(p))
#undef FAIL
{}

void dht_config_global::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(static_nodes_, s);
  TlStoreBinary::store(k_, s);
  TlStoreBinary::store(a_, s);
}

void dht_config_global::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(static_nodes_, s);
  TlStoreBinary::store(k_, s);
  TlStoreBinary::store(a_, s);
}

void dht_config_global::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_config_global");
    if (static_nodes_ == nullptr) { s.store_field("static_nodes", "null"); } else { static_nodes_->store(s, "static_nodes"); }
    s.store_field("k", k_);
    s.store_field("a", a_);
    s.store_class_end();
  }
}

object_storage<dht_config_Local> dht_config_Local::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case dht_config_local::ID:
      return dht_config_local::fetch(p);
    case dht_config_random_local::ID:
      return dht_config_random_local::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

dht_config_local::dht_config_local()
  : id_()
{}

dht_config_local::dht_config_local(object_storage<adnl_id_short> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t dht_config_local::ID;

dht_config_local::dht_config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_short>::parse(p))
#undef FAIL
{}

void dht_config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void dht_config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void dht_config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_config_local");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

dht_config_random_local::dht_config_random_local()
  : cnt_()
  , addr_list_()
{}

dht_config_random_local::dht_config_random_local(std::int32_t cnt_, object_storage<adnl_addressList> &&addr_list_)
  : cnt_(cnt_)
  , addr_list_(std::move(addr_list_))
{}

const std::int32_t dht_config_random_local::ID;

dht_config_random_local::dht_config_random_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : cnt_(TlFetchInt::parse(p))
  , addr_list_(TlFetchObject<adnl_addressList>::parse(p))
#undef FAIL
{}

void dht_config_random_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(cnt_, s);
  TlStoreObject::store(addr_list_, s);
}

void dht_config_random_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(cnt_, s);
  TlStoreObject::store(addr_list_, s);
}

void dht_config_random_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_config_random_local");
    s.store_field("cnt", cnt_);
    if (addr_list_ == nullptr) { s.store_field("addr_list", "null"); } else { addr_list_->store(s, "addr_list"); }
    s.store_class_end();
  }
}

dummydb_block::dummydb_block()
  : id_()
  , flags_()
  , prev_()
  , next_()
  , lt_()
  , state_()
  , state_file_()
  , proof_()
  , proof_link_()
  , signatures_()
{}

dummydb_block::dummydb_block(object_storage<tonNode_blockIdExt> &&id_, std::int32_t flags_, std::vector<object_storage<tonNode_blockIdExt>> &&prev_, std::vector<object_storage<tonNode_blockIdExt>> &&next_, std::int64_t lt_, td::UInt256 const &state_, td::UInt256 const &state_file_, td::UInt256 const &proof_, td::UInt256 const &proof_link_, td::UInt256 const &signatures_)
  : id_(std::move(id_))
  , flags_(flags_)
  , prev_(std::move(prev_))
  , next_(std::move(next_))
  , lt_(lt_)
  , state_(state_)
  , state_file_(state_file_)
  , proof_(proof_)
  , proof_link_(proof_link_)
  , signatures_(signatures_)
{}

const std::int32_t dummydb_block::ID;

dummydb_block::dummydb_block(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , flags_(TlFetchInt::parse(p))
  , prev_(TlFetchVector<TlFetchObject<tonNode_blockIdExt>>::parse(p))
  , next_(TlFetchVector<TlFetchObject<tonNode_blockIdExt>>::parse(p))
  , lt_(TlFetchLong::parse(p))
  , state_(TlFetchInt256::parse(p))
  , state_file_(TlFetchInt256::parse(p))
  , proof_(TlFetchInt256::parse(p))
  , proof_link_(TlFetchInt256::parse(p))
  , signatures_(TlFetchInt256::parse(p))
#undef FAIL
{}

void dummydb_block::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreBinary::store(flags_, s);
  TlStoreVector<TlStoreObject>::store(prev_, s);
  TlStoreVector<TlStoreObject>::store(next_, s);
  TlStoreBinary::store(lt_, s);
  TlStoreBinary::store(state_, s);
  TlStoreBinary::store(state_file_, s);
  TlStoreBinary::store(proof_, s);
  TlStoreBinary::store(proof_link_, s);
  TlStoreBinary::store(signatures_, s);
}

void dummydb_block::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreBinary::store(flags_, s);
  TlStoreVector<TlStoreObject>::store(prev_, s);
  TlStoreVector<TlStoreObject>::store(next_, s);
  TlStoreBinary::store(lt_, s);
  TlStoreBinary::store(state_, s);
  TlStoreBinary::store(state_file_, s);
  TlStoreBinary::store(proof_, s);
  TlStoreBinary::store(proof_link_, s);
  TlStoreBinary::store(signatures_, s);
}

void dummydb_block::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dummydb_block");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("flags", flags_);
    { const std::vector<object_storage<tonNode_blockIdExt>> &v = prev_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("prev", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<tonNode_blockIdExt>> &v = next_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("next", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_field("lt", lt_);
    s.store_field("state", state_);
    s.store_field("state_file", state_file_);
    s.store_field("proof", proof_);
    s.store_field("proof_link", proof_link_);
    s.store_field("signatures", signatures_);
    s.store_class_end();
  }
}

dummydb_gcValidatorSessionList::dummydb_gcValidatorSessionList()
  : list_()
{}

dummydb_gcValidatorSessionList::dummydb_gcValidatorSessionList(std::vector<td::UInt256> &&list_)
  : list_(std::move(list_))
{}

const std::int32_t dummydb_gcValidatorSessionList::ID;

dummydb_gcValidatorSessionList::dummydb_gcValidatorSessionList(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : list_(TlFetchVector<TlFetchInt256>::parse(p))
#undef FAIL
{}

void dummydb_gcValidatorSessionList::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(list_, s);
}

void dummydb_gcValidatorSessionList::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(list_, s);
}

void dummydb_gcValidatorSessionList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dummydb_gcValidatorSessionList");
    { const std::vector<td::UInt256> &v = list_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("list", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

dummyworkchain0_config_global::dummyworkchain0_config_global()
  : zero_state_hash_()
{}

dummyworkchain0_config_global::dummyworkchain0_config_global(td::UInt256 const &zero_state_hash_)
  : zero_state_hash_(zero_state_hash_)
{}

const std::int32_t dummyworkchain0_config_global::ID;

dummyworkchain0_config_global::dummyworkchain0_config_global(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : zero_state_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void dummyworkchain0_config_global::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(zero_state_hash_, s);
}

void dummyworkchain0_config_global::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(zero_state_hash_, s);
}

void dummyworkchain0_config_global::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dummyworkchain0_config_global");
    s.store_field("zero_state_hash", zero_state_hash_);
    s.store_class_end();
  }
}

dummyworkchain0_config_local::dummyworkchain0_config_local()
  : id_()
{}

dummyworkchain0_config_local::dummyworkchain0_config_local(object_storage<adnl_id_short> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t dummyworkchain0_config_local::ID;

dummyworkchain0_config_local::dummyworkchain0_config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_short>::parse(p))
#undef FAIL
{}

void dummyworkchain0_config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void dummyworkchain0_config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void dummyworkchain0_config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dummyworkchain0_config_local");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

object_storage<fer_Type> fer_Type::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case fer_raptorQ::ID:
      return fer_raptorQ::fetch(p);
    case fer_simple::ID:
      return fer_simple::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

fer_raptorQ::fer_raptorQ()
  : symbol_size_()
  , total_symbols_()
  , total_size_()
{}

fer_raptorQ::fer_raptorQ(std::int32_t symbol_size_, std::int32_t total_symbols_, std::int32_t total_size_)
  : symbol_size_(symbol_size_)
  , total_symbols_(total_symbols_)
  , total_size_(total_size_)
{}

const std::int32_t fer_raptorQ::ID;

fer_raptorQ::fer_raptorQ(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : symbol_size_(TlFetchInt::parse(p))
  , total_symbols_(TlFetchInt::parse(p))
  , total_size_(TlFetchInt::parse(p))
#undef FAIL
{}

void fer_raptorQ::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(symbol_size_, s);
  TlStoreBinary::store(total_symbols_, s);
  TlStoreBinary::store(total_size_, s);
}

void fer_raptorQ::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(symbol_size_, s);
  TlStoreBinary::store(total_symbols_, s);
  TlStoreBinary::store(total_size_, s);
}

void fer_raptorQ::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "fer_raptorQ");
    s.store_field("symbol_size", symbol_size_);
    s.store_field("total_symbols", total_symbols_);
    s.store_field("total_size", total_size_);
    s.store_class_end();
  }
}

fer_simple::fer_simple()
  : symbol_size_()
  , total_symbols_()
  , total_size_()
{}

fer_simple::fer_simple(std::int32_t symbol_size_, std::int32_t total_symbols_, std::int32_t total_size_)
  : symbol_size_(symbol_size_)
  , total_symbols_(total_symbols_)
  , total_size_(total_size_)
{}

const std::int32_t fer_simple::ID;

fer_simple::fer_simple(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : symbol_size_(TlFetchInt::parse(p))
  , total_symbols_(TlFetchInt::parse(p))
  , total_size_(TlFetchInt::parse(p))
#undef FAIL
{}

void fer_simple::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(symbol_size_, s);
  TlStoreBinary::store(total_symbols_, s);
  TlStoreBinary::store(total_size_, s);
}

void fer_simple::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(symbol_size_, s);
  TlStoreBinary::store(total_symbols_, s);
  TlStoreBinary::store(total_size_, s);
}

void fer_simple::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "fer_simple");
    s.store_field("symbol_size", symbol_size_);
    s.store_field("total_symbols", total_symbols_);
    s.store_field("total_size", total_size_);
    s.store_class_end();
  }
}

id_config_local::id_config_local()
  : id_()
  , addr_list_()
{}

id_config_local::id_config_local(object_storage<adnl_id_Pk> &&id_, object_storage<adnl_addressList> &&addr_list_)
  : id_(std::move(id_))
  , addr_list_(std::move(addr_list_))
{}

const std::int32_t id_config_local::ID;

id_config_local::id_config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_Pk>::parse(p))
  , addr_list_(TlFetchObject<adnl_addressList>::parse(p))
#undef FAIL
{}

void id_config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreObject::store(addr_list_, s);
}

void id_config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreObject::store(addr_list_, s);
}

void id_config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "id_config_local");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    if (addr_list_ == nullptr) { s.store_field("addr_list", "null"); } else { addr_list_->store(s, "addr_list"); }
    s.store_class_end();
  }
}

liteServer_accountId::liteServer_accountId()
  : workchain_()
  , id_()
{}

liteServer_accountId::liteServer_accountId(std::int32_t workchain_, td::UInt256 const &id_)
  : workchain_(workchain_)
  , id_(id_)
{}

const std::int32_t liteServer_accountId::ID;

liteServer_accountId::liteServer_accountId(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , id_(TlFetchInt256::parse(p))
#undef FAIL
{}

void liteServer_accountId::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(id_, s);
}

void liteServer_accountId::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(id_, s);
}

void liteServer_accountId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_accountId");
    s.store_field("workchain", workchain_);
    s.store_field("id", id_);
    s.store_class_end();
  }
}

liteServer_accountState::liteServer_accountState()
  : id_()
  , shardblk_()
  , shard_proof_()
  , proof_()
  , state_()
{}

liteServer_accountState::liteServer_accountState(object_storage<tonNode_blockIdExt> &&id_, object_storage<tonNode_blockIdExt> &&shardblk_, td::BufferSlice &&shard_proof_, td::BufferSlice &&proof_, td::BufferSlice &&state_)
  : id_(std::move(id_))
  , shardblk_(std::move(shardblk_))
  , shard_proof_(std::move(shard_proof_))
  , proof_(std::move(proof_))
  , state_(std::move(state_))
{}

const std::int32_t liteServer_accountState::ID;

liteServer_accountState::liteServer_accountState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , shardblk_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , shard_proof_(TlFetchBytes<td::BufferSlice>::parse(p))
  , proof_(TlFetchBytes<td::BufferSlice>::parse(p))
  , state_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void liteServer_accountState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreObject::store(shardblk_, s);
  TlStoreString::store(shard_proof_, s);
  TlStoreString::store(proof_, s);
  TlStoreString::store(state_, s);
}

void liteServer_accountState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreObject::store(shardblk_, s);
  TlStoreString::store(shard_proof_, s);
  TlStoreString::store(proof_, s);
  TlStoreString::store(state_, s);
}

void liteServer_accountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_accountState");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    if (shardblk_ == nullptr) { s.store_field("shardblk", "null"); } else { shardblk_->store(s, "shardblk"); }
    s.store_bytes_field("shard_proof", shard_proof_);
    s.store_bytes_field("proof", proof_);
    s.store_bytes_field("state", state_);
    s.store_class_end();
  }
}

liteServer_blockData::liteServer_blockData()
  : id_()
  , data_()
{}

liteServer_blockData::liteServer_blockData(object_storage<tonNode_blockIdExt> &&id_, td::BufferSlice &&data_)
  : id_(std::move(id_))
  , data_(std::move(data_))
{}

const std::int32_t liteServer_blockData::ID;

liteServer_blockData::liteServer_blockData(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void liteServer_blockData::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreString::store(data_, s);
}

void liteServer_blockData::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreString::store(data_, s);
}

void liteServer_blockData::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_blockData");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

liteServer_blockState::liteServer_blockState()
  : id_()
  , root_hash_()
  , file_hash_()
  , data_()
{}

liteServer_blockState::liteServer_blockState(object_storage<tonNode_blockIdExt> &&id_, td::UInt256 const &root_hash_, td::UInt256 const &file_hash_, td::BufferSlice &&data_)
  : id_(std::move(id_))
  , root_hash_(root_hash_)
  , file_hash_(file_hash_)
  , data_(std::move(data_))
{}

const std::int32_t liteServer_blockState::ID;

liteServer_blockState::liteServer_blockState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , root_hash_(TlFetchInt256::parse(p))
  , file_hash_(TlFetchInt256::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void liteServer_blockState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreString::store(data_, s);
}

void liteServer_blockState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreString::store(data_, s);
}

void liteServer_blockState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_blockState");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("root_hash", root_hash_);
    s.store_field("file_hash", file_hash_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

liteServer_currentTime::liteServer_currentTime()
  : now_()
{}

liteServer_currentTime::liteServer_currentTime(std::int32_t now_)
  : now_(now_)
{}

const std::int32_t liteServer_currentTime::ID;

liteServer_currentTime::liteServer_currentTime(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : now_(TlFetchInt::parse(p))
#undef FAIL
{}

void liteServer_currentTime::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(now_, s);
}

void liteServer_currentTime::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(now_, s);
}

void liteServer_currentTime::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_currentTime");
    s.store_field("now", now_);
    s.store_class_end();
  }
}

liteServer_error::liteServer_error()
  : code_()
  , message_()
{}

liteServer_error::liteServer_error(std::int32_t code_, std::string const &message_)
  : code_(code_)
  , message_(message_)
{}

const std::int32_t liteServer_error::ID;

liteServer_error::liteServer_error(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : code_(TlFetchInt::parse(p))
  , message_(TlFetchString<std::string>::parse(p))
#undef FAIL
{}

void liteServer_error::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(code_, s);
  TlStoreString::store(message_, s);
}

void liteServer_error::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(code_, s);
  TlStoreString::store(message_, s);
}

void liteServer_error::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_error");
    s.store_field("code", code_);
    s.store_field("message", message_);
    s.store_class_end();
  }
}

liteServer_masterchainInfo::liteServer_masterchainInfo()
  : last_()
  , state_root_hash_()
  , init_()
{}

liteServer_masterchainInfo::liteServer_masterchainInfo(object_storage<tonNode_blockIdExt> &&last_, td::UInt256 const &state_root_hash_, object_storage<tonNode_zeroStateIdExt> &&init_)
  : last_(std::move(last_))
  , state_root_hash_(state_root_hash_)
  , init_(std::move(init_))
{}

const std::int32_t liteServer_masterchainInfo::ID;

liteServer_masterchainInfo::liteServer_masterchainInfo(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : last_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , state_root_hash_(TlFetchInt256::parse(p))
  , init_(TlFetchObject<tonNode_zeroStateIdExt>::parse(p))
#undef FAIL
{}

void liteServer_masterchainInfo::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(last_, s);
  TlStoreBinary::store(state_root_hash_, s);
  TlStoreObject::store(init_, s);
}

void liteServer_masterchainInfo::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(last_, s);
  TlStoreBinary::store(state_root_hash_, s);
  TlStoreObject::store(init_, s);
}

void liteServer_masterchainInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_masterchainInfo");
    if (last_ == nullptr) { s.store_field("last", "null"); } else { last_->store(s, "last"); }
    s.store_field("state_root_hash", state_root_hash_);
    if (init_ == nullptr) { s.store_field("init", "null"); } else { init_->store(s, "init"); }
    s.store_class_end();
  }
}

liteServer_sendMsgStatus::liteServer_sendMsgStatus()
  : status_()
{}

liteServer_sendMsgStatus::liteServer_sendMsgStatus(std::int32_t status_)
  : status_(status_)
{}

const std::int32_t liteServer_sendMsgStatus::ID;

liteServer_sendMsgStatus::liteServer_sendMsgStatus(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : status_(TlFetchInt::parse(p))
#undef FAIL
{}

void liteServer_sendMsgStatus::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(status_, s);
}

void liteServer_sendMsgStatus::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(status_, s);
}

void liteServer_sendMsgStatus::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_sendMsgStatus");
    s.store_field("status", status_);
    s.store_class_end();
  }
}

liteServer_debug_verbosity::liteServer_debug_verbosity()
  : value_()
{}

liteServer_debug_verbosity::liteServer_debug_verbosity(std::int32_t value_)
  : value_(value_)
{}

const std::int32_t liteServer_debug_verbosity::ID;

liteServer_debug_verbosity::liteServer_debug_verbosity(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchInt::parse(p))
#undef FAIL
{}

void liteServer_debug_verbosity::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void liteServer_debug_verbosity::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(value_, s);
}

void liteServer_debug_verbosity::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_debug_verbosity");
    s.store_field("value", value_);
    s.store_class_end();
  }
}

liteclient_config_global::liteclient_config_global()
  : id_()
  , ip_()
  , port_()
{}

liteclient_config_global::liteclient_config_global(object_storage<adnl_id_Full> &&id_, std::int32_t ip_, std::int32_t port_)
  : id_(std::move(id_))
  , ip_(ip_)
  , port_(port_)
{}

const std::int32_t liteclient_config_global::ID;

liteclient_config_global::liteclient_config_global(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_Full>::parse(p))
  , ip_(TlFetchInt::parse(p))
  , port_(TlFetchInt::parse(p))
#undef FAIL
{}

void liteclient_config_global::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void liteclient_config_global::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBinary::store(ip_, s);
  TlStoreBinary::store(port_, s);
}

void liteclient_config_global::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteclient_config_global");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("ip", ip_);
    s.store_field("port", port_);
    s.store_class_end();
  }
}

liteserver_config_local::liteserver_config_local()
  : id_()
  , port_()
{}

liteserver_config_local::liteserver_config_local(object_storage<adnl_id_Pk> &&id_, std::int32_t port_)
  : id_(std::move(id_))
  , port_(port_)
{}

const std::int32_t liteserver_config_local::ID;

liteserver_config_local::liteserver_config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_Pk>::parse(p))
  , port_(TlFetchInt::parse(p))
#undef FAIL
{}

void liteserver_config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBinary::store(port_, s);
}

void liteserver_config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBinary::store(port_, s);
}

void liteserver_config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteserver_config_local");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("port", port_);
    s.store_class_end();
  }
}

object_storage<overlay_Broadcast> overlay_Broadcast::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case overlay_fer_received::ID:
      return overlay_fer_received::fetch(p);
    case overlay_fer_completed::ID:
      return overlay_fer_completed::fetch(p);
    case overlay_unicast::ID:
      return overlay_unicast::fetch(p);
    case overlay_broadcast::ID:
      return overlay_broadcast::fetch(p);
    case overlay_broadcastFer::ID:
      return overlay_broadcastFer::fetch(p);
    case overlay_broadcastFerShort::ID:
      return overlay_broadcastFerShort::fetch(p);
    case overlay_broadcastNotFound::ID:
      return overlay_broadcastNotFound::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

overlay_fer_received::overlay_fer_received()
  : hash_()
{}

overlay_fer_received::overlay_fer_received(td::UInt256 const &hash_)
  : hash_(hash_)
{}

const std::int32_t overlay_fer_received::ID;

overlay_fer_received::overlay_fer_received(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void overlay_fer_received::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
}

void overlay_fer_received::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
}

void overlay_fer_received::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_fer_received");
    s.store_field("hash", hash_);
    s.store_class_end();
  }
}

overlay_fer_completed::overlay_fer_completed()
  : hash_()
{}

overlay_fer_completed::overlay_fer_completed(td::UInt256 const &hash_)
  : hash_(hash_)
{}

const std::int32_t overlay_fer_completed::ID;

overlay_fer_completed::overlay_fer_completed(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void overlay_fer_completed::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
}

void overlay_fer_completed::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
}

void overlay_fer_completed::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_fer_completed");
    s.store_field("hash", hash_);
    s.store_class_end();
  }
}

overlay_unicast::overlay_unicast()
  : data_()
{}

overlay_unicast::overlay_unicast(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t overlay_unicast::ID;

overlay_unicast::overlay_unicast(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void overlay_unicast::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void overlay_unicast::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void overlay_unicast::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_unicast");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

overlay_broadcast::overlay_broadcast()
  : src_()
  , data_()
  , date_()
  , signature_()
{}

overlay_broadcast::overlay_broadcast(object_storage<adnl_id_Full> &&src_, td::BufferSlice &&data_, std::int32_t date_, td::BufferSlice &&signature_)
  : src_(std::move(src_))
  , data_(std::move(data_))
  , date_(date_)
  , signature_(std::move(signature_))
{}

const std::int32_t overlay_broadcast::ID;

overlay_broadcast::overlay_broadcast(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : src_(TlFetchObject<adnl_id_Full>::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
  , date_(TlFetchInt::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void overlay_broadcast::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(src_, s);
  TlStoreString::store(data_, s);
  TlStoreBinary::store(date_, s);
  TlStoreString::store(signature_, s);
}

void overlay_broadcast::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(src_, s);
  TlStoreString::store(data_, s);
  TlStoreBinary::store(date_, s);
  TlStoreString::store(signature_, s);
}

void overlay_broadcast::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_broadcast");
    if (src_ == nullptr) { s.store_field("src", "null"); } else { src_->store(s, "src"); }
    s.store_bytes_field("data", data_);
    s.store_field("date", date_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

overlay_broadcastFer::overlay_broadcastFer()
  : src_()
  , hash_()
  , data_()
  , seqno_()
  , fer_()
  , date_()
  , signature_()
{}

overlay_broadcastFer::overlay_broadcastFer(object_storage<adnl_id_Full> &&src_, td::UInt256 const &hash_, td::BufferSlice &&data_, std::int32_t seqno_, object_storage<fer_Type> &&fer_, std::int32_t date_, td::BufferSlice &&signature_)
  : src_(std::move(src_))
  , hash_(hash_)
  , data_(std::move(data_))
  , seqno_(seqno_)
  , fer_(std::move(fer_))
  , date_(date_)
  , signature_(std::move(signature_))
{}

const std::int32_t overlay_broadcastFer::ID;

overlay_broadcastFer::overlay_broadcastFer(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : src_(TlFetchObject<adnl_id_Full>::parse(p))
  , hash_(TlFetchInt256::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , fer_(TlFetchObject<fer_Type>::parse(p))
  , date_(TlFetchInt::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void overlay_broadcastFer::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(src_, s);
  TlStoreBinary::store(hash_, s);
  TlStoreString::store(data_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(fer_, s);
  TlStoreBinary::store(date_, s);
  TlStoreString::store(signature_, s);
}

void overlay_broadcastFer::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(src_, s);
  TlStoreBinary::store(hash_, s);
  TlStoreString::store(data_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(fer_, s);
  TlStoreBinary::store(date_, s);
  TlStoreString::store(signature_, s);
}

void overlay_broadcastFer::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_broadcastFer");
    if (src_ == nullptr) { s.store_field("src", "null"); } else { src_->store(s, "src"); }
    s.store_field("hash", hash_);
    s.store_bytes_field("data", data_);
    s.store_field("seqno", seqno_);
    if (fer_ == nullptr) { s.store_field("fer", "null"); } else { fer_->store(s, "fer"); }
    s.store_field("date", date_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

overlay_broadcastFerShort::overlay_broadcastFerShort()
  : hash_()
  , seqno_()
  , signature_()
{}

overlay_broadcastFerShort::overlay_broadcastFerShort(td::UInt256 const &hash_, std::int32_t seqno_, td::BufferSlice &&signature_)
  : hash_(hash_)
  , seqno_(seqno_)
  , signature_(std::move(signature_))
{}

const std::int32_t overlay_broadcastFerShort::ID;

overlay_broadcastFerShort::overlay_broadcastFerShort(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void overlay_broadcastFerShort::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreString::store(signature_, s);
}

void overlay_broadcastFerShort::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreString::store(signature_, s);
}

void overlay_broadcastFerShort::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_broadcastFerShort");
    s.store_field("hash", hash_);
    s.store_field("seqno", seqno_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

overlay_broadcastNotFound::overlay_broadcastNotFound() {
}

const std::int32_t overlay_broadcastNotFound::ID;

overlay_broadcastNotFound::overlay_broadcastNotFound(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void overlay_broadcastNotFound::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void overlay_broadcastNotFound::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void overlay_broadcastNotFound::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_broadcastNotFound");
    s.store_class_end();
  }
}

overlay_broadcastList::overlay_broadcastList()
  : hashes_()
{}

overlay_broadcastList::overlay_broadcastList(std::vector<td::UInt256> &&hashes_)
  : hashes_(std::move(hashes_))
{}

const std::int32_t overlay_broadcastList::ID;

overlay_broadcastList::overlay_broadcastList(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hashes_(TlFetchVector<TlFetchInt256>::parse(p))
#undef FAIL
{}

void overlay_broadcastList::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(hashes_, s);
}

void overlay_broadcastList::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreBinary>::store(hashes_, s);
}

void overlay_broadcastList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_broadcastList");
    { const std::vector<td::UInt256> &v = hashes_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("hashes", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

overlay_message::overlay_message()
  : overlay_()
{}

overlay_message::overlay_message(td::UInt256 const &overlay_)
  : overlay_(overlay_)
{}

const std::int32_t overlay_message::ID;

overlay_message::overlay_message(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : overlay_(TlFetchInt256::parse(p))
#undef FAIL
{}

void overlay_message::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(overlay_, s);
}

void overlay_message::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(overlay_, s);
}

void overlay_message::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_message");
    s.store_field("overlay", overlay_);
    s.store_class_end();
  }
}

overlay_node::overlay_node()
  : id_()
  , overlay_()
  , version_()
  , signature_()
{}

overlay_node::overlay_node(object_storage<adnl_id_Full> &&id_, td::UInt256 const &overlay_, std::int32_t version_, td::BufferSlice &&signature_)
  : id_(std::move(id_))
  , overlay_(overlay_)
  , version_(version_)
  , signature_(std::move(signature_))
{}

const std::int32_t overlay_node::ID;

overlay_node::overlay_node(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_Full>::parse(p))
  , overlay_(TlFetchInt256::parse(p))
  , version_(TlFetchInt::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void overlay_node::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBinary::store(overlay_, s);
  TlStoreBinary::store(version_, s);
  TlStoreString::store(signature_, s);
}

void overlay_node::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBoxedUnknown<TlStoreObject>::store(id_, s);
  TlStoreBinary::store(overlay_, s);
  TlStoreBinary::store(version_, s);
  TlStoreString::store(signature_, s);
}

void overlay_node::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_node");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("overlay", overlay_);
    s.store_field("version", version_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

overlay_nodes::overlay_nodes()
  : nodes_()
{}

overlay_nodes::overlay_nodes(std::vector<object_storage<overlay_node>> &&nodes_)
  : nodes_(std::move(nodes_))
{}

const std::int32_t overlay_nodes::ID;

overlay_nodes::overlay_nodes(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : nodes_(TlFetchVector<TlFetchObject<overlay_node>>::parse(p))
#undef FAIL
{}

void overlay_nodes::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(nodes_, s);
}

void overlay_nodes::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(nodes_, s);
}

void overlay_nodes::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_nodes");
    { const std::vector<object_storage<overlay_node>> &v = nodes_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("nodes", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

overlay_broadcastFer_id::overlay_broadcastFer_id()
  : src_()
  , type_()
  , hash_()
  , date_()
{}

overlay_broadcastFer_id::overlay_broadcastFer_id(td::UInt256 const &src_, td::UInt256 const &type_, td::UInt256 const &hash_, std::int32_t date_)
  : src_(src_)
  , type_(type_)
  , hash_(hash_)
  , date_(date_)
{}

const std::int32_t overlay_broadcastFer_id::ID;

overlay_broadcastFer_id::overlay_broadcastFer_id(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : src_(TlFetchInt256::parse(p))
  , type_(TlFetchInt256::parse(p))
  , hash_(TlFetchInt256::parse(p))
  , date_(TlFetchInt::parse(p))
#undef FAIL
{}

void overlay_broadcastFer_id::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(type_, s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(date_, s);
}

void overlay_broadcastFer_id::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(type_, s);
  TlStoreBinary::store(hash_, s);
  TlStoreBinary::store(date_, s);
}

void overlay_broadcastFer_id::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_broadcastFer_id");
    s.store_field("src", src_);
    s.store_field("type", type_);
    s.store_field("hash", hash_);
    s.store_field("date", date_);
    s.store_class_end();
  }
}

object_storage<overlay_config_Local> overlay_config_Local::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case overlay_config_local::ID:
      return overlay_config_local::fetch(p);
    case overlay_config_random_local::ID:
      return overlay_config_random_local::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

overlay_config_local::overlay_config_local()
  : name_()
  , id_()
{}

overlay_config_local::overlay_config_local(td::BufferSlice &&name_, object_storage<adnl_id_short> &&id_)
  : name_(std::move(name_))
  , id_(std::move(id_))
{}

const std::int32_t overlay_config_local::ID;

overlay_config_local::overlay_config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : name_(TlFetchBytes<td::BufferSlice>::parse(p))
  , id_(TlFetchObject<adnl_id_short>::parse(p))
#undef FAIL
{}

void overlay_config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(name_, s);
  TlStoreObject::store(id_, s);
}

void overlay_config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(name_, s);
  TlStoreObject::store(id_, s);
}

void overlay_config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_config_local");
    s.store_bytes_field("name", name_);
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

overlay_config_random_local::overlay_config_random_local()
  : cnt_()
  , name_()
  , addr_list_()
{}

overlay_config_random_local::overlay_config_random_local(std::int32_t cnt_, td::BufferSlice &&name_, object_storage<adnl_addressList> &&addr_list_)
  : cnt_(cnt_)
  , name_(std::move(name_))
  , addr_list_(std::move(addr_list_))
{}

const std::int32_t overlay_config_random_local::ID;

overlay_config_random_local::overlay_config_random_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : cnt_(TlFetchInt::parse(p))
  , name_(TlFetchBytes<td::BufferSlice>::parse(p))
  , addr_list_(TlFetchObject<adnl_addressList>::parse(p))
#undef FAIL
{}

void overlay_config_random_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(cnt_, s);
  TlStoreString::store(name_, s);
  TlStoreObject::store(addr_list_, s);
}

void overlay_config_random_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(cnt_, s);
  TlStoreString::store(name_, s);
  TlStoreObject::store(addr_list_, s);
}

void overlay_config_random_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_config_random_local");
    s.store_field("cnt", cnt_);
    s.store_bytes_field("name", name_);
    if (addr_list_ == nullptr) { s.store_field("addr_list", "null"); } else { addr_list_->store(s, "addr_list"); }
    s.store_class_end();
  }
}

object_storage<rldp_Message> rldp_Message::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case rldp_message::ID:
      return rldp_message::fetch(p);
    case rldp_query::ID:
      return rldp_query::fetch(p);
    case rldp_answer::ID:
      return rldp_answer::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

rldp_message::rldp_message()
  : id_()
  , data_()
{}

rldp_message::rldp_message(td::UInt256 const &id_, td::BufferSlice &&data_)
  : id_(id_)
  , data_(std::move(data_))
{}

const std::int32_t rldp_message::ID;

rldp_message::rldp_message(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchInt256::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void rldp_message::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
  TlStoreString::store(data_, s);
}

void rldp_message::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
  TlStoreString::store(data_, s);
}

void rldp_message::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rldp_message");
    s.store_field("id", id_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

rldp_query::rldp_query()
  : query_id_()
  , data_()
{}

rldp_query::rldp_query(td::UInt256 const &query_id_, td::BufferSlice &&data_)
  : query_id_(query_id_)
  , data_(std::move(data_))
{}

const std::int32_t rldp_query::ID;

rldp_query::rldp_query(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : query_id_(TlFetchInt256::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void rldp_query::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(data_, s);
}

void rldp_query::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(data_, s);
}

void rldp_query::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rldp_query");
    s.store_field("query_id", query_id_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

rldp_answer::rldp_answer()
  : query_id_()
  , data_()
{}

rldp_answer::rldp_answer(td::UInt256 const &query_id_, td::BufferSlice &&data_)
  : query_id_(query_id_)
  , data_(std::move(data_))
{}

const std::int32_t rldp_answer::ID;

rldp_answer::rldp_answer(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : query_id_(TlFetchInt256::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void rldp_answer::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(data_, s);
}

void rldp_answer::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(query_id_, s);
  TlStoreString::store(data_, s);
}

void rldp_answer::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rldp_answer");
    s.store_field("query_id", query_id_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

object_storage<rldp_MessagePart> rldp_MessagePart::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case rldp_messagePart::ID:
      return rldp_messagePart::fetch(p);
    case rldp_confirm::ID:
      return rldp_confirm::fetch(p);
    case rldp_complete::ID:
      return rldp_complete::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

rldp_messagePart::rldp_messagePart()
  : transfer_id_()
  , fer_type_()
  , part_()
  , total_size_()
  , seqno_()
  , data_()
{}

rldp_messagePart::rldp_messagePart(td::UInt256 const &transfer_id_, object_storage<fer_Type> &&fer_type_, std::int32_t part_, std::int64_t total_size_, std::int32_t seqno_, td::BufferSlice &&data_)
  : transfer_id_(transfer_id_)
  , fer_type_(std::move(fer_type_))
  , part_(part_)
  , total_size_(total_size_)
  , seqno_(seqno_)
  , data_(std::move(data_))
{}

const std::int32_t rldp_messagePart::ID;

rldp_messagePart::rldp_messagePart(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : transfer_id_(TlFetchInt256::parse(p))
  , fer_type_(TlFetchObject<fer_Type>::parse(p))
  , part_(TlFetchInt::parse(p))
  , total_size_(TlFetchLong::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void rldp_messagePart::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(transfer_id_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(fer_type_, s);
  TlStoreBinary::store(part_, s);
  TlStoreBinary::store(total_size_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreString::store(data_, s);
}

void rldp_messagePart::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(transfer_id_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(fer_type_, s);
  TlStoreBinary::store(part_, s);
  TlStoreBinary::store(total_size_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreString::store(data_, s);
}

void rldp_messagePart::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rldp_messagePart");
    s.store_field("transfer_id", transfer_id_);
    if (fer_type_ == nullptr) { s.store_field("fer_type", "null"); } else { fer_type_->store(s, "fer_type"); }
    s.store_field("part", part_);
    s.store_field("total_size", total_size_);
    s.store_field("seqno", seqno_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

rldp_confirm::rldp_confirm()
  : transfer_id_()
  , part_()
  , seqno_()
{}

rldp_confirm::rldp_confirm(td::UInt256 const &transfer_id_, std::int32_t part_, std::int32_t seqno_)
  : transfer_id_(transfer_id_)
  , part_(part_)
  , seqno_(seqno_)
{}

const std::int32_t rldp_confirm::ID;

rldp_confirm::rldp_confirm(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : transfer_id_(TlFetchInt256::parse(p))
  , part_(TlFetchInt::parse(p))
  , seqno_(TlFetchInt::parse(p))
#undef FAIL
{}

void rldp_confirm::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(transfer_id_, s);
  TlStoreBinary::store(part_, s);
  TlStoreBinary::store(seqno_, s);
}

void rldp_confirm::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(transfer_id_, s);
  TlStoreBinary::store(part_, s);
  TlStoreBinary::store(seqno_, s);
}

void rldp_confirm::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rldp_confirm");
    s.store_field("transfer_id", transfer_id_);
    s.store_field("part", part_);
    s.store_field("seqno", seqno_);
    s.store_class_end();
  }
}

rldp_complete::rldp_complete()
  : transfer_id_()
  , part_()
{}

rldp_complete::rldp_complete(td::UInt256 const &transfer_id_, std::int32_t part_)
  : transfer_id_(transfer_id_)
  , part_(part_)
{}

const std::int32_t rldp_complete::ID;

rldp_complete::rldp_complete(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : transfer_id_(TlFetchInt256::parse(p))
  , part_(TlFetchInt::parse(p))
#undef FAIL
{}

void rldp_complete::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(transfer_id_, s);
  TlStoreBinary::store(part_, s);
}

void rldp_complete::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(transfer_id_, s);
  TlStoreBinary::store(part_, s);
}

void rldp_complete::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "rldp_complete");
    s.store_field("transfer_id", transfer_id_);
    s.store_field("part", part_);
    s.store_class_end();
  }
}

tcp_pong::tcp_pong()
  : random_id_()
{}

tcp_pong::tcp_pong(std::int64_t random_id_)
  : random_id_(random_id_)
{}

const std::int32_t tcp_pong::ID;

tcp_pong::tcp_pong(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : random_id_(TlFetchLong::parse(p))
#undef FAIL
{}

void tcp_pong::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(random_id_, s);
}

void tcp_pong::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(random_id_, s);
}

void tcp_pong::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tcp_pong");
    s.store_field("random_id", random_id_);
    s.store_class_end();
  }
}

test0_proof::test0_proof()
  : link_()
  , validator_set_ts_()
  , validator_set_hash_()
  , signatures_()
{}

test0_proof::test0_proof(object_storage<test0_proofLink> &&link_, std::int32_t validator_set_ts_, std::int32_t validator_set_hash_, object_storage<test0_blockSignatures> &&signatures_)
  : link_(std::move(link_))
  , validator_set_ts_(validator_set_ts_)
  , validator_set_hash_(validator_set_hash_)
  , signatures_(std::move(signatures_))
{}

const std::int32_t test0_proof::ID;

test0_proof::test0_proof(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : link_(TlFetchObject<test0_proofLink>::parse(p))
  , validator_set_ts_(TlFetchInt::parse(p))
  , validator_set_hash_(TlFetchInt::parse(p))
  , signatures_(TlFetchObject<test0_blockSignatures>::parse(p))
#undef FAIL
{}

void test0_proof::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(link_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreObject::store(signatures_, s);
}

void test0_proof::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(link_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreObject::store(signatures_, s);
}

void test0_proof::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_proof");
    if (link_ == nullptr) { s.store_field("link", "null"); } else { link_->store(s, "link"); }
    s.store_field("validator_set_ts", validator_set_ts_);
    s.store_field("validator_set_hash", validator_set_hash_);
    if (signatures_ == nullptr) { s.store_field("signatures", "null"); } else { signatures_->store(s, "signatures"); }
    s.store_class_end();
  }
}

test0_proofLink::test0_proofLink()
  : id_()
  , prev_()
  , state_()
  , split_()
{}

test0_proofLink::test0_proofLink(object_storage<tonNode_blockIdExt> &&id_, std::vector<object_storage<tonNode_blockIdExt>> &&prev_, td::UInt256 const &state_, bool split_)
  : id_(std::move(id_))
  , prev_(std::move(prev_))
  , state_(state_)
  , split_(split_)
{}

const std::int32_t test0_proofLink::ID;

test0_proofLink::test0_proofLink(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , prev_(TlFetchVector<TlFetchObject<tonNode_blockIdExt>>::parse(p))
  , state_(TlFetchInt256::parse(p))
  , split_(TlFetchBool::parse(p))
#undef FAIL
{}

void test0_proofLink::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreVector<TlStoreObject>::store(prev_, s);
  TlStoreBinary::store(state_, s);
  TlStoreBool::store(split_, s);
}

void test0_proofLink::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreVector<TlStoreObject>::store(prev_, s);
  TlStoreBinary::store(state_, s);
  TlStoreBool::store(split_, s);
}

void test0_proofLink::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_proofLink");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    { const std::vector<object_storage<tonNode_blockIdExt>> &v = prev_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("prev", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_field("state", state_);
    s.store_field("split", split_);
    s.store_class_end();
  }
}

test0_shardchain_block::test0_shardchain_block()
  : workchain_()
  , shard_()
  , seqno_()
  , prev_()
  , split_()
  , ts_()
  , state_()
  , validator_set_ts_()
  , validator_set_hash_()
  , pad_()
  , extra_()
{}

test0_shardchain_block::test0_shardchain_block(std::int32_t workchain_, std::int64_t shard_, std::int32_t seqno_, std::vector<object_storage<tonNode_blockIdExt>> &&prev_, bool split_, std::int32_t ts_, td::UInt256 const &state_, std::int32_t validator_set_ts_, std::int32_t validator_set_hash_, td::BufferSlice &&pad_, object_storage<test0_MasterchainBlockExtra> &&extra_)
  : workchain_(workchain_)
  , shard_(shard_)
  , seqno_(seqno_)
  , prev_(std::move(prev_))
  , split_(split_)
  , ts_(ts_)
  , state_(state_)
  , validator_set_ts_(validator_set_ts_)
  , validator_set_hash_(validator_set_hash_)
  , pad_(std::move(pad_))
  , extra_(std::move(extra_))
{}

const std::int32_t test0_shardchain_block::ID;

test0_shardchain_block::test0_shardchain_block(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , prev_(TlFetchVector<TlFetchObject<tonNode_blockIdExt>>::parse(p))
  , split_(TlFetchBool::parse(p))
  , ts_(TlFetchInt::parse(p))
  , state_(TlFetchInt256::parse(p))
  , validator_set_ts_(TlFetchInt::parse(p))
  , validator_set_hash_(TlFetchInt::parse(p))
  , pad_(TlFetchBytes<td::BufferSlice>::parse(p))
  , extra_(TlFetchObject<test0_MasterchainBlockExtra>::parse(p))
#undef FAIL
{}

void test0_shardchain_block::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreVector<TlStoreObject>::store(prev_, s);
  TlStoreBool::store(split_, s);
  TlStoreBinary::store(ts_, s);
  TlStoreBinary::store(state_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreString::store(pad_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(extra_, s);
}

void test0_shardchain_block::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreVector<TlStoreObject>::store(prev_, s);
  TlStoreBool::store(split_, s);
  TlStoreBinary::store(ts_, s);
  TlStoreBinary::store(state_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreString::store(pad_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(extra_, s);
}

void test0_shardchain_block::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_shardchain_block");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_field("seqno", seqno_);
    { const std::vector<object_storage<tonNode_blockIdExt>> &v = prev_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("prev", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_field("split", split_);
    s.store_field("ts", ts_);
    s.store_field("state", state_);
    s.store_field("validator_set_ts", validator_set_ts_);
    s.store_field("validator_set_hash", validator_set_hash_);
    s.store_bytes_field("pad", pad_);
    if (extra_ == nullptr) { s.store_field("extra", "null"); } else { extra_->store(s, "extra"); }
    s.store_class_end();
  }
}

test0_shardchain_state::test0_shardchain_state()
  : workchain_()
  , shard_()
  , seqno_()
  , ts_()
  , split_()
  , extra_()
{}

test0_shardchain_state::test0_shardchain_state(std::int32_t workchain_, std::int64_t shard_, std::int32_t seqno_, std::int32_t ts_, bool split_, object_storage<test0_MasterchainStateExtra> &&extra_)
  : workchain_(workchain_)
  , shard_(shard_)
  , seqno_(seqno_)
  , ts_(ts_)
  , split_(split_)
  , extra_(std::move(extra_))
{}

const std::int32_t test0_shardchain_state::ID;

test0_shardchain_state::test0_shardchain_state(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , ts_(TlFetchInt::parse(p))
  , split_(TlFetchBool::parse(p))
  , extra_(TlFetchObject<test0_MasterchainStateExtra>::parse(p))
#undef FAIL
{}

void test0_shardchain_state::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(ts_, s);
  TlStoreBool::store(split_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(extra_, s);
}

void test0_shardchain_state::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(ts_, s);
  TlStoreBool::store(split_, s);
  TlStoreBoxedUnknown<TlStoreObject>::store(extra_, s);
}

void test0_shardchain_state::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_shardchain_state");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_field("seqno", seqno_);
    s.store_field("ts", ts_);
    s.store_field("split", split_);
    if (extra_ == nullptr) { s.store_field("extra", "null"); } else { extra_->store(s, "extra"); }
    s.store_class_end();
  }
}

test_validatorSession_block::test_validatorSession_block()
  : root_hash_()
  , height_()
  , data_()
{}

test_validatorSession_block::test_validatorSession_block(td::UInt256 const &root_hash_, std::int64_t height_, td::BufferSlice &&data_)
  : root_hash_(root_hash_)
  , height_(height_)
  , data_(std::move(data_))
{}

const std::int32_t test_validatorSession_block::ID;

test_validatorSession_block::test_validatorSession_block(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : root_hash_(TlFetchInt256::parse(p))
  , height_(TlFetchLong::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void test_validatorSession_block::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(height_, s);
  TlStoreString::store(data_, s);
}

void test_validatorSession_block::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(height_, s);
  TlStoreString::store(data_, s);
}

void test_validatorSession_block::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test_validatorSession_block");
    s.store_field("root_hash", root_hash_);
    s.store_field("height", height_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

test0_blockSignatures::test0_blockSignatures()
  : signatures_()
{}

test0_blockSignatures::test0_blockSignatures(std::vector<object_storage<tonNode_blockSignature>> &&signatures_)
  : signatures_(std::move(signatures_))
{}

const std::int32_t test0_blockSignatures::ID;

test0_blockSignatures::test0_blockSignatures(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : signatures_(TlFetchVector<TlFetchObject<tonNode_blockSignature>>::parse(p))
#undef FAIL
{}

void test0_blockSignatures::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(signatures_, s);
}

void test0_blockSignatures::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreVector<TlStoreObject>::store(signatures_, s);
}

void test0_blockSignatures::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_blockSignatures");
    { const std::vector<object_storage<tonNode_blockSignature>> &v = signatures_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("signatures", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

test0_extMessage::test0_extMessage()
  : workchain_()
  , shard_()
  , data_()
{}

test0_extMessage::test0_extMessage(std::int32_t workchain_, std::int64_t shard_, td::BufferSlice &&data_)
  : workchain_(workchain_)
  , shard_(shard_)
  , data_(std::move(data_))
{}

const std::int32_t test0_extMessage::ID;

test0_extMessage::test0_extMessage(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void test0_extMessage::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreString::store(data_, s);
}

void test0_extMessage::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreString::store(data_, s);
}

void test0_extMessage::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_extMessage");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

object_storage<test0_MasterchainBlockExtra> test0_MasterchainBlockExtra::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case test0_masterchainBlockExtra_empty::ID:
      return test0_masterchainBlockExtra_empty::fetch(p);
    case test0_masterchainBlockExtra_extra::ID:
      return test0_masterchainBlockExtra_extra::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

test0_masterchainBlockExtra_empty::test0_masterchainBlockExtra_empty() {
}

const std::int32_t test0_masterchainBlockExtra_empty::ID;

test0_masterchainBlockExtra_empty::test0_masterchainBlockExtra_empty(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void test0_masterchainBlockExtra_empty::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void test0_masterchainBlockExtra_empty::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void test0_masterchainBlockExtra_empty::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_masterchainBlockExtra_empty");
    s.store_class_end();
  }
}

test0_masterchainBlockExtra_extra::test0_masterchainBlockExtra_extra()
  : randseed_()
  , rotate_()
  , shards_()
{}

test0_masterchainBlockExtra_extra::test0_masterchainBlockExtra_extra(std::int32_t randseed_, bool rotate_, std::vector<object_storage<test0_masterchain_shardInfo>> &&shards_)
  : randseed_(randseed_)
  , rotate_(rotate_)
  , shards_(std::move(shards_))
{}

const std::int32_t test0_masterchainBlockExtra_extra::ID;

test0_masterchainBlockExtra_extra::test0_masterchainBlockExtra_extra(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : randseed_(TlFetchInt::parse(p))
  , rotate_(TlFetchBool::parse(p))
  , shards_(TlFetchVector<TlFetchObject<test0_masterchain_shardInfo>>::parse(p))
#undef FAIL
{}

void test0_masterchainBlockExtra_extra::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(randseed_, s);
  TlStoreBool::store(rotate_, s);
  TlStoreVector<TlStoreObject>::store(shards_, s);
}

void test0_masterchainBlockExtra_extra::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(randseed_, s);
  TlStoreBool::store(rotate_, s);
  TlStoreVector<TlStoreObject>::store(shards_, s);
}

void test0_masterchainBlockExtra_extra::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_masterchainBlockExtra_extra");
    s.store_field("randseed", randseed_);
    s.store_field("rotate", rotate_);
    { const std::vector<object_storage<test0_masterchain_shardInfo>> &v = shards_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("shards", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

object_storage<test0_MasterchainStateExtra> test0_MasterchainStateExtra::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case test0_masterchainStateExtra_empty::ID:
      return test0_masterchainStateExtra_empty::fetch(p);
    case test0_masterchainStateExtra_extra::ID:
      return test0_masterchainStateExtra_extra::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

test0_masterchainStateExtra_empty::test0_masterchainStateExtra_empty() {
}

const std::int32_t test0_masterchainStateExtra_empty::ID;

test0_masterchainStateExtra_empty::test0_masterchainStateExtra_empty(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void test0_masterchainStateExtra_empty::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void test0_masterchainStateExtra_empty::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void test0_masterchainStateExtra_empty::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_masterchainStateExtra_empty");
    s.store_class_end();
  }
}

test0_masterchainStateExtra_extra::test0_masterchainStateExtra_extra()
  : validator_ts_()
  , validator_randseed_()
  , next_randseed_()
  , next_rotate_at_()
  , prev_blocks_()
  , shards_()
  , pool_()
{}

test0_masterchainStateExtra_extra::test0_masterchainStateExtra_extra(std::int32_t validator_ts_, std::int32_t validator_randseed_, std::int32_t next_randseed_, std::int32_t next_rotate_at_, std::vector<object_storage<tonNode_blockIdExt>> &&prev_blocks_, std::vector<object_storage<test0_masterchain_shardInfo>> &&shards_, std::vector<object_storage<adnl_id_Full>> &&pool_)
  : validator_ts_(validator_ts_)
  , validator_randseed_(validator_randseed_)
  , next_randseed_(next_randseed_)
  , next_rotate_at_(next_rotate_at_)
  , prev_blocks_(std::move(prev_blocks_))
  , shards_(std::move(shards_))
  , pool_(std::move(pool_))
{}

const std::int32_t test0_masterchainStateExtra_extra::ID;

test0_masterchainStateExtra_extra::test0_masterchainStateExtra_extra(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : validator_ts_(TlFetchInt::parse(p))
  , validator_randseed_(TlFetchInt::parse(p))
  , next_randseed_(TlFetchInt::parse(p))
  , next_rotate_at_(TlFetchInt::parse(p))
  , prev_blocks_(TlFetchVector<TlFetchObject<tonNode_blockIdExt>>::parse(p))
  , shards_(TlFetchVector<TlFetchObject<test0_masterchain_shardInfo>>::parse(p))
  , pool_(TlFetchVector<TlFetchObject<adnl_id_Full>>::parse(p))
#undef FAIL
{}

void test0_masterchainStateExtra_extra::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(validator_ts_, s);
  TlStoreBinary::store(validator_randseed_, s);
  TlStoreBinary::store(next_randseed_, s);
  TlStoreBinary::store(next_rotate_at_, s);
  TlStoreVector<TlStoreObject>::store(prev_blocks_, s);
  TlStoreVector<TlStoreObject>::store(shards_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(pool_, s);
}

void test0_masterchainStateExtra_extra::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(validator_ts_, s);
  TlStoreBinary::store(validator_randseed_, s);
  TlStoreBinary::store(next_randseed_, s);
  TlStoreBinary::store(next_rotate_at_, s);
  TlStoreVector<TlStoreObject>::store(prev_blocks_, s);
  TlStoreVector<TlStoreObject>::store(shards_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(pool_, s);
}

void test0_masterchainStateExtra_extra::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_masterchainStateExtra_extra");
    s.store_field("validator_ts", validator_ts_);
    s.store_field("validator_randseed", validator_randseed_);
    s.store_field("next_randseed", next_randseed_);
    s.store_field("next_rotate_at", next_rotate_at_);
    { const std::vector<object_storage<tonNode_blockIdExt>> &v = prev_blocks_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("prev_blocks", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<test0_masterchain_shardInfo>> &v = shards_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("shards", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    { const std::vector<object_storage<adnl_id_Full>> &v = pool_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("pool", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

test0_topShardBlockDescription::test0_topShardBlockDescription()
  : block_id_()
  , after_split_()
  , after_merge_()
  , before_split_()
  , validator_set_ts_()
  , validator_set_hash_()
  , signatures_()
{}

test0_topShardBlockDescription::test0_topShardBlockDescription(object_storage<tonNode_blockIdExt> &&block_id_, bool after_split_, bool after_merge_, bool before_split_, std::int32_t validator_set_ts_, std::int32_t validator_set_hash_, td::BufferSlice &&signatures_)
  : block_id_(std::move(block_id_))
  , after_split_(after_split_)
  , after_merge_(after_merge_)
  , before_split_(before_split_)
  , validator_set_ts_(validator_set_ts_)
  , validator_set_hash_(validator_set_hash_)
  , signatures_(std::move(signatures_))
{}

const std::int32_t test0_topShardBlockDescription::ID;

test0_topShardBlockDescription::test0_topShardBlockDescription(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , after_split_(TlFetchBool::parse(p))
  , after_merge_(TlFetchBool::parse(p))
  , before_split_(TlFetchBool::parse(p))
  , validator_set_ts_(TlFetchInt::parse(p))
  , validator_set_hash_(TlFetchInt::parse(p))
  , signatures_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void test0_topShardBlockDescription::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_id_, s);
  TlStoreBool::store(after_split_, s);
  TlStoreBool::store(after_merge_, s);
  TlStoreBool::store(before_split_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreString::store(signatures_, s);
}

void test0_topShardBlockDescription::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_id_, s);
  TlStoreBool::store(after_split_, s);
  TlStoreBool::store(after_merge_, s);
  TlStoreBool::store(before_split_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreString::store(signatures_, s);
}

void test0_topShardBlockDescription::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_topShardBlockDescription");
    if (block_id_ == nullptr) { s.store_field("block_id", "null"); } else { block_id_->store(s, "block_id"); }
    s.store_field("after_split", after_split_);
    s.store_field("after_merge", after_merge_);
    s.store_field("before_split", before_split_);
    s.store_field("validator_set_ts", validator_set_ts_);
    s.store_field("validator_set_hash", validator_set_hash_);
    s.store_bytes_field("signatures", signatures_);
    s.store_class_end();
  }
}

test0_validatorSessionId::test0_validatorSessionId()
  : workchain_()
  , shard_()
  , shard_from_()
  , ts_()
{}

test0_validatorSessionId::test0_validatorSessionId(std::int32_t workchain_, std::int64_t shard_, std::int64_t shard_from_, std::int32_t ts_)
  : workchain_(workchain_)
  , shard_(shard_)
  , shard_from_(shard_from_)
  , ts_(ts_)
{}

const std::int32_t test0_validatorSessionId::ID;

test0_validatorSessionId::test0_validatorSessionId(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
  , shard_from_(TlFetchLong::parse(p))
  , ts_(TlFetchInt::parse(p))
#undef FAIL
{}

void test0_validatorSessionId::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(shard_from_, s);
  TlStoreBinary::store(ts_, s);
}

void test0_validatorSessionId::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(shard_from_, s);
  TlStoreBinary::store(ts_, s);
}

void test0_validatorSessionId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_validatorSessionId");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_field("shard_from", shard_from_);
    s.store_field("ts", ts_);
    s.store_class_end();
  }
}

test0_validatorSet::test0_validatorSet()
  : ts_()
  , validators_()
{}

test0_validatorSet::test0_validatorSet(std::int32_t ts_, std::vector<object_storage<test0_validatorSetItem>> &&validators_)
  : ts_(ts_)
  , validators_(std::move(validators_))
{}

const std::int32_t test0_validatorSet::ID;

test0_validatorSet::test0_validatorSet(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : ts_(TlFetchInt::parse(p))
  , validators_(TlFetchVector<TlFetchObject<test0_validatorSetItem>>::parse(p))
#undef FAIL
{}

void test0_validatorSet::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ts_, s);
  TlStoreVector<TlStoreObject>::store(validators_, s);
}

void test0_validatorSet::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ts_, s);
  TlStoreVector<TlStoreObject>::store(validators_, s);
}

void test0_validatorSet::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_validatorSet");
    s.store_field("ts", ts_);
    { const std::vector<object_storage<test0_validatorSetItem>> &v = validators_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("validators", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_class_end();
  }
}

test0_validatorSetItem::test0_validatorSetItem()
  : id_()
  , weight_()
{}

test0_validatorSetItem::test0_validatorSetItem(td::UInt256 const &id_, std::int64_t weight_)
  : id_(id_)
  , weight_(weight_)
{}

const std::int32_t test0_validatorSetItem::ID;

test0_validatorSetItem::test0_validatorSetItem(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchInt256::parse(p))
  , weight_(TlFetchLong::parse(p))
#undef FAIL
{}

void test0_validatorSetItem::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
  TlStoreBinary::store(weight_, s);
}

void test0_validatorSetItem::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(id_, s);
  TlStoreBinary::store(weight_, s);
}

void test0_validatorSetItem::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_validatorSetItem");
    s.store_field("id", id_);
    s.store_field("weight", weight_);
    s.store_class_end();
  }
}

test0_masterchain_shardInfo::test0_masterchain_shardInfo()
  : last_block_()
  , before_merge_()
  , before_split_()
  , after_merge_()
  , after_split_()
{}

test0_masterchain_shardInfo::test0_masterchain_shardInfo(object_storage<tonNode_blockIdExt> &&last_block_, bool before_merge_, bool before_split_, bool after_merge_, bool after_split_)
  : last_block_(std::move(last_block_))
  , before_merge_(before_merge_)
  , before_split_(before_split_)
  , after_merge_(after_merge_)
  , after_split_(after_split_)
{}

const std::int32_t test0_masterchain_shardInfo::ID;

test0_masterchain_shardInfo::test0_masterchain_shardInfo(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : last_block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , before_merge_(TlFetchBool::parse(p))
  , before_split_(TlFetchBool::parse(p))
  , after_merge_(TlFetchBool::parse(p))
  , after_split_(TlFetchBool::parse(p))
#undef FAIL
{}

void test0_masterchain_shardInfo::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(last_block_, s);
  TlStoreBool::store(before_merge_, s);
  TlStoreBool::store(before_split_, s);
  TlStoreBool::store(after_merge_, s);
  TlStoreBool::store(after_split_, s);
}

void test0_masterchain_shardInfo::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(last_block_, s);
  TlStoreBool::store(before_merge_, s);
  TlStoreBool::store(before_split_, s);
  TlStoreBool::store(after_merge_, s);
  TlStoreBool::store(after_split_, s);
}

void test0_masterchain_shardInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "test0_masterchain_shardInfo");
    if (last_block_ == nullptr) { s.store_field("last_block", "null"); } else { last_block_->store(s, "last_block"); }
    s.store_field("before_merge", before_merge_);
    s.store_field("before_split", before_split_);
    s.store_field("after_merge", after_merge_);
    s.store_field("after_split", after_split_);
    s.store_class_end();
  }
}

ton_blockId::ton_blockId()
  : root_cell_hash_()
  , file_hash_()
{}

ton_blockId::ton_blockId(td::UInt256 const &root_cell_hash_, td::UInt256 const &file_hash_)
  : root_cell_hash_(root_cell_hash_)
  , file_hash_(file_hash_)
{}

const std::int32_t ton_blockId::ID;

ton_blockId::ton_blockId(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : root_cell_hash_(TlFetchInt256::parse(p))
  , file_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void ton_blockId::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(root_cell_hash_, s);
  TlStoreBinary::store(file_hash_, s);
}

void ton_blockId::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(root_cell_hash_, s);
  TlStoreBinary::store(file_hash_, s);
}

void ton_blockId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "ton_blockId");
    s.store_field("root_cell_hash", root_cell_hash_);
    s.store_field("file_hash", file_hash_);
    s.store_class_end();
  }
}

object_storage<tonNode_BlockDescription> tonNode_BlockDescription::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case tonNode_blockDescriptionEmpty::ID:
      return tonNode_blockDescriptionEmpty::fetch(p);
    case tonNode_blockDescription::ID:
      return tonNode_blockDescription::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

tonNode_blockDescriptionEmpty::tonNode_blockDescriptionEmpty() {
}

const std::int32_t tonNode_blockDescriptionEmpty::ID;

tonNode_blockDescriptionEmpty::tonNode_blockDescriptionEmpty(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void tonNode_blockDescriptionEmpty::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void tonNode_blockDescriptionEmpty::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void tonNode_blockDescriptionEmpty::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_blockDescriptionEmpty");
    s.store_class_end();
  }
}

tonNode_blockDescription::tonNode_blockDescription()
  : id_()
{}

tonNode_blockDescription::tonNode_blockDescription(object_storage<tonNode_blockIdExt> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t tonNode_blockDescription::ID;

tonNode_blockDescription::tonNode_blockDescription(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_blockDescription::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void tonNode_blockDescription::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void tonNode_blockDescription::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_blockDescription");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

tonNode_blockIdExt::tonNode_blockIdExt()
  : workchain_()
  , shard_()
  , seqno_()
  , root_hash_()
  , file_hash_()
{}

tonNode_blockIdExt::tonNode_blockIdExt(std::int32_t workchain_, std::int64_t shard_, std::int32_t seqno_, td::UInt256 const &root_hash_, td::UInt256 const &file_hash_)
  : workchain_(workchain_)
  , shard_(shard_)
  , seqno_(seqno_)
  , root_hash_(root_hash_)
  , file_hash_(file_hash_)
{}

const std::int32_t tonNode_blockIdExt::ID;

tonNode_blockIdExt::tonNode_blockIdExt(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
  , seqno_(TlFetchInt::parse(p))
  , root_hash_(TlFetchInt256::parse(p))
  , file_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void tonNode_blockIdExt::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
}

void tonNode_blockIdExt::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(seqno_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
}

void tonNode_blockIdExt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_blockIdExt");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_field("seqno", seqno_);
    s.store_field("root_hash", root_hash_);
    s.store_field("file_hash", file_hash_);
    s.store_class_end();
  }
}

tonNode_blockSignature::tonNode_blockSignature()
  : who_()
  , signature_()
{}

tonNode_blockSignature::tonNode_blockSignature(td::UInt256 const &who_, td::BufferSlice &&signature_)
  : who_(who_)
  , signature_(std::move(signature_))
{}

const std::int32_t tonNode_blockSignature::ID;

tonNode_blockSignature::tonNode_blockSignature(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : who_(TlFetchInt256::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void tonNode_blockSignature::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(who_, s);
  TlStoreString::store(signature_, s);
}

void tonNode_blockSignature::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(who_, s);
  TlStoreString::store(signature_, s);
}

void tonNode_blockSignature::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_blockSignature");
    s.store_field("who", who_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

object_storage<tonNode_Broadcast> tonNode_Broadcast::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case tonNode_blockBroadcast::ID:
      return tonNode_blockBroadcast::fetch(p);
    case tonNode_ihrMessageBroadcast::ID:
      return tonNode_ihrMessageBroadcast::fetch(p);
    case tonNode_externalMessageBroadcast::ID:
      return tonNode_externalMessageBroadcast::fetch(p);
    case tonNode_newShardBlockBroadcast::ID:
      return tonNode_newShardBlockBroadcast::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

tonNode_blockBroadcast::tonNode_blockBroadcast()
  : id_()
  , validator_set_ts_()
  , validator_set_hash_()
  , signatures_()
  , masterchain_block_id_()
  , proof_()
  , data_()
{}

tonNode_blockBroadcast::tonNode_blockBroadcast(object_storage<tonNode_blockIdExt> &&id_, std::int32_t validator_set_ts_, std::int32_t validator_set_hash_, std::vector<object_storage<tonNode_blockSignature>> &&signatures_, object_storage<tonNode_blockIdExt> &&masterchain_block_id_, td::BufferSlice &&proof_, td::BufferSlice &&data_)
  : id_(std::move(id_))
  , validator_set_ts_(validator_set_ts_)
  , validator_set_hash_(validator_set_hash_)
  , signatures_(std::move(signatures_))
  , masterchain_block_id_(std::move(masterchain_block_id_))
  , proof_(std::move(proof_))
  , data_(std::move(data_))
{}

const std::int32_t tonNode_blockBroadcast::ID;

tonNode_blockBroadcast::tonNode_blockBroadcast(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , validator_set_ts_(TlFetchInt::parse(p))
  , validator_set_hash_(TlFetchInt::parse(p))
  , signatures_(TlFetchVector<TlFetchObject<tonNode_blockSignature>>::parse(p))
  , masterchain_block_id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , proof_(TlFetchBytes<td::BufferSlice>::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void tonNode_blockBroadcast::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreVector<TlStoreObject>::store(signatures_, s);
  TlStoreObject::store(masterchain_block_id_, s);
  TlStoreString::store(proof_, s);
  TlStoreString::store(data_, s);
}

void tonNode_blockBroadcast::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
  TlStoreBinary::store(validator_set_ts_, s);
  TlStoreBinary::store(validator_set_hash_, s);
  TlStoreVector<TlStoreObject>::store(signatures_, s);
  TlStoreObject::store(masterchain_block_id_, s);
  TlStoreString::store(proof_, s);
  TlStoreString::store(data_, s);
}

void tonNode_blockBroadcast::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_blockBroadcast");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_field("validator_set_ts", validator_set_ts_);
    s.store_field("validator_set_hash", validator_set_hash_);
    { const std::vector<object_storage<tonNode_blockSignature>> &v = signatures_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("signatures", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    if (masterchain_block_id_ == nullptr) { s.store_field("masterchain_block_id", "null"); } else { masterchain_block_id_->store(s, "masterchain_block_id"); }
    s.store_bytes_field("proof", proof_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

tonNode_ihrMessageBroadcast::tonNode_ihrMessageBroadcast()
  : message_()
{}

tonNode_ihrMessageBroadcast::tonNode_ihrMessageBroadcast(object_storage<tonNode_ihrMessage> &&message_)
  : message_(std::move(message_))
{}

const std::int32_t tonNode_ihrMessageBroadcast::ID;

tonNode_ihrMessageBroadcast::tonNode_ihrMessageBroadcast(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : message_(TlFetchObject<tonNode_ihrMessage>::parse(p))
#undef FAIL
{}

void tonNode_ihrMessageBroadcast::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(message_, s);
}

void tonNode_ihrMessageBroadcast::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(message_, s);
}

void tonNode_ihrMessageBroadcast::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_ihrMessageBroadcast");
    if (message_ == nullptr) { s.store_field("message", "null"); } else { message_->store(s, "message"); }
    s.store_class_end();
  }
}

tonNode_externalMessageBroadcast::tonNode_externalMessageBroadcast()
  : message_()
{}

tonNode_externalMessageBroadcast::tonNode_externalMessageBroadcast(object_storage<tonNode_externalMessage> &&message_)
  : message_(std::move(message_))
{}

const std::int32_t tonNode_externalMessageBroadcast::ID;

tonNode_externalMessageBroadcast::tonNode_externalMessageBroadcast(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : message_(TlFetchObject<tonNode_externalMessage>::parse(p))
#undef FAIL
{}

void tonNode_externalMessageBroadcast::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(message_, s);
}

void tonNode_externalMessageBroadcast::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(message_, s);
}

void tonNode_externalMessageBroadcast::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_externalMessageBroadcast");
    if (message_ == nullptr) { s.store_field("message", "null"); } else { message_->store(s, "message"); }
    s.store_class_end();
  }
}

tonNode_newShardBlockBroadcast::tonNode_newShardBlockBroadcast()
  : block_()
{}

tonNode_newShardBlockBroadcast::tonNode_newShardBlockBroadcast(object_storage<tonNode_newShardBlock> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t tonNode_newShardBlockBroadcast::ID;

tonNode_newShardBlockBroadcast::tonNode_newShardBlockBroadcast(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_newShardBlock>::parse(p))
#undef FAIL
{}

void tonNode_newShardBlockBroadcast::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void tonNode_newShardBlockBroadcast::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(block_, s);
}

void tonNode_newShardBlockBroadcast::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_newShardBlockBroadcast");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

tonNode_data::tonNode_data()
  : data_()
{}

tonNode_data::tonNode_data(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t tonNode_data::ID;

tonNode_data::tonNode_data(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void tonNode_data::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void tonNode_data::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void tonNode_data::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_data");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

tonNode_externalMessage::tonNode_externalMessage()
  : data_()
{}

tonNode_externalMessage::tonNode_externalMessage(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t tonNode_externalMessage::ID;

tonNode_externalMessage::tonNode_externalMessage(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void tonNode_externalMessage::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void tonNode_externalMessage::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void tonNode_externalMessage::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_externalMessage");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

tonNode_ihrMessage::tonNode_ihrMessage()
  : data_()
{}

tonNode_ihrMessage::tonNode_ihrMessage(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t tonNode_ihrMessage::ID;

tonNode_ihrMessage::tonNode_ihrMessage(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void tonNode_ihrMessage::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void tonNode_ihrMessage::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreString::store(data_, s);
}

void tonNode_ihrMessage::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_ihrMessage");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

tonNode_newShardBlock::tonNode_newShardBlock()
  : workchain_()
  , shard_()
  , data_()
{}

tonNode_newShardBlock::tonNode_newShardBlock(std::int32_t workchain_, std::int64_t shard_, td::BufferSlice &&data_)
  : workchain_(workchain_)
  , shard_(shard_)
  , data_(std::move(data_))
{}

const std::int32_t tonNode_newShardBlock::ID;

tonNode_newShardBlock::tonNode_newShardBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void tonNode_newShardBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreString::store(data_, s);
}

void tonNode_newShardBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreString::store(data_, s);
}

void tonNode_newShardBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_newShardBlock");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

object_storage<tonNode_Prepared> tonNode_Prepared::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case tonNode_prepared::ID:
      return tonNode_prepared::fetch(p);
    case tonNode_notFound::ID:
      return tonNode_notFound::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

tonNode_prepared::tonNode_prepared() {
}

const std::int32_t tonNode_prepared::ID;

tonNode_prepared::tonNode_prepared(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void tonNode_prepared::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void tonNode_prepared::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void tonNode_prepared::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_prepared");
    s.store_class_end();
  }
}

tonNode_notFound::tonNode_notFound() {
}

const std::int32_t tonNode_notFound::ID;

tonNode_notFound::tonNode_notFound(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void tonNode_notFound::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void tonNode_notFound::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void tonNode_notFound::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_notFound");
    s.store_class_end();
  }
}

object_storage<tonNode_PreparedProof> tonNode_PreparedProof::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case tonNode_preparedProofEmpty::ID:
      return tonNode_preparedProofEmpty::fetch(p);
    case tonNode_preparedProof::ID:
      return tonNode_preparedProof::fetch(p);
    case tonNode_preparedProofLink::ID:
      return tonNode_preparedProofLink::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

tonNode_preparedProofEmpty::tonNode_preparedProofEmpty() {
}

const std::int32_t tonNode_preparedProofEmpty::ID;

tonNode_preparedProofEmpty::tonNode_preparedProofEmpty(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void tonNode_preparedProofEmpty::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void tonNode_preparedProofEmpty::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void tonNode_preparedProofEmpty::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_preparedProofEmpty");
    s.store_class_end();
  }
}

tonNode_preparedProof::tonNode_preparedProof()
  : masterchain_block_()
{}

tonNode_preparedProof::tonNode_preparedProof(object_storage<tonNode_blockIdExt> &&masterchain_block_)
  : masterchain_block_(std::move(masterchain_block_))
{}

const std::int32_t tonNode_preparedProof::ID;

tonNode_preparedProof::tonNode_preparedProof(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : masterchain_block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_preparedProof::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(masterchain_block_, s);
}

void tonNode_preparedProof::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(masterchain_block_, s);
}

void tonNode_preparedProof::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_preparedProof");
    if (masterchain_block_ == nullptr) { s.store_field("masterchain_block", "null"); } else { masterchain_block_->store(s, "masterchain_block"); }
    s.store_class_end();
  }
}

tonNode_preparedProofLink::tonNode_preparedProofLink() {
}

const std::int32_t tonNode_preparedProofLink::ID;

tonNode_preparedProofLink::tonNode_preparedProofLink(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void tonNode_preparedProofLink::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void tonNode_preparedProofLink::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void tonNode_preparedProofLink::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_preparedProofLink");
    s.store_class_end();
  }
}

object_storage<tonNode_PreparedState> tonNode_PreparedState::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case tonNode_preparedState::ID:
      return tonNode_preparedState::fetch(p);
    case tonNode_notFoundState::ID:
      return tonNode_notFoundState::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

tonNode_preparedState::tonNode_preparedState() {
}

const std::int32_t tonNode_preparedState::ID;

tonNode_preparedState::tonNode_preparedState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void tonNode_preparedState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void tonNode_preparedState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void tonNode_preparedState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_preparedState");
    s.store_class_end();
  }
}

tonNode_notFoundState::tonNode_notFoundState() {
}

const std::int32_t tonNode_notFoundState::ID;

tonNode_notFoundState::tonNode_notFoundState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void tonNode_notFoundState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void tonNode_notFoundState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void tonNode_notFoundState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_notFoundState");
    s.store_class_end();
  }
}

tonNode_sessionId::tonNode_sessionId()
  : workchain_()
  , shard_()
  , utime_from_()
  , utime_to_()
{}

tonNode_sessionId::tonNode_sessionId(std::int32_t workchain_, std::int64_t shard_, std::int32_t utime_from_, std::int32_t utime_to_)
  : workchain_(workchain_)
  , shard_(shard_)
  , utime_from_(utime_from_)
  , utime_to_(utime_to_)
{}

const std::int32_t tonNode_sessionId::ID;

tonNode_sessionId::tonNode_sessionId(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
  , utime_from_(TlFetchInt::parse(p))
  , utime_to_(TlFetchInt::parse(p))
#undef FAIL
{}

void tonNode_sessionId::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(utime_from_, s);
  TlStoreBinary::store(utime_to_, s);
}

void tonNode_sessionId::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
  TlStoreBinary::store(utime_from_, s);
  TlStoreBinary::store(utime_to_, s);
}

void tonNode_sessionId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_sessionId");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_field("utime_from", utime_from_);
    s.store_field("utime_to", utime_to_);
    s.store_class_end();
  }
}

tonNode_shardPublicOverlayId::tonNode_shardPublicOverlayId()
  : workchain_()
  , shard_()
{}

tonNode_shardPublicOverlayId::tonNode_shardPublicOverlayId(std::int32_t workchain_, std::int64_t shard_)
  : workchain_(workchain_)
  , shard_(shard_)
{}

const std::int32_t tonNode_shardPublicOverlayId::ID;

tonNode_shardPublicOverlayId::tonNode_shardPublicOverlayId(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , shard_(TlFetchLong::parse(p))
#undef FAIL
{}

void tonNode_shardPublicOverlayId::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
}

void tonNode_shardPublicOverlayId::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(shard_, s);
}

void tonNode_shardPublicOverlayId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_shardPublicOverlayId");
    s.store_field("workchain", workchain_);
    s.store_field("shard", shard_);
    s.store_class_end();
  }
}

tonNode_zeroStateIdExt::tonNode_zeroStateIdExt()
  : workchain_()
  , root_hash_()
  , file_hash_()
{}

tonNode_zeroStateIdExt::tonNode_zeroStateIdExt(std::int32_t workchain_, td::UInt256 const &root_hash_, td::UInt256 const &file_hash_)
  : workchain_(workchain_)
  , root_hash_(root_hash_)
  , file_hash_(file_hash_)
{}

const std::int32_t tonNode_zeroStateIdExt::ID;

tonNode_zeroStateIdExt::tonNode_zeroStateIdExt(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : workchain_(TlFetchInt::parse(p))
  , root_hash_(TlFetchInt256::parse(p))
  , file_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void tonNode_zeroStateIdExt::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
}

void tonNode_zeroStateIdExt::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(workchain_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
}

void tonNode_zeroStateIdExt::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_zeroStateIdExt");
    s.store_field("workchain", workchain_);
    s.store_field("root_hash", root_hash_);
    s.store_field("file_hash", file_hash_);
    s.store_class_end();
  }
}

validator_config_global::validator_config_global()
  : zero_state_root_hash_()
  , zero_state_file_hash_()
{}

validator_config_global::validator_config_global(td::UInt256 const &zero_state_root_hash_, td::UInt256 const &zero_state_file_hash_)
  : zero_state_root_hash_(zero_state_root_hash_)
  , zero_state_file_hash_(zero_state_file_hash_)
{}

const std::int32_t validator_config_global::ID;

validator_config_global::validator_config_global(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : zero_state_root_hash_(TlFetchInt256::parse(p))
  , zero_state_file_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void validator_config_global::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(zero_state_root_hash_, s);
  TlStoreBinary::store(zero_state_file_hash_, s);
}

void validator_config_global::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(zero_state_root_hash_, s);
  TlStoreBinary::store(zero_state_file_hash_, s);
}

void validator_config_global::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validator_config_global");
    s.store_field("zero_state_root_hash", zero_state_root_hash_);
    s.store_field("zero_state_file_hash", zero_state_file_hash_);
    s.store_class_end();
  }
}

validator_config_local::validator_config_local()
  : id_()
{}

validator_config_local::validator_config_local(object_storage<adnl_id_short> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t validator_config_local::ID;

validator_config_local::validator_config_local(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<adnl_id_short>::parse(p))
#undef FAIL
{}

void validator_config_local::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void validator_config_local::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreObject::store(id_, s);
}

void validator_config_local::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validator_config_local");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

validatorSession_blockUpdate::validatorSession_blockUpdate()
  : ts_()
  , actions_()
  , state_()
{}

validatorSession_blockUpdate::validatorSession_blockUpdate(std::int64_t ts_, std::vector<object_storage<validatorSession_round_Message>> &&actions_, std::int32_t state_)
  : ts_(ts_)
  , actions_(std::move(actions_))
  , state_(state_)
{}

const std::int32_t validatorSession_blockUpdate::ID;

validatorSession_blockUpdate::validatorSession_blockUpdate(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : ts_(TlFetchLong::parse(p))
  , actions_(TlFetchVector<TlFetchObject<validatorSession_round_Message>>::parse(p))
  , state_(TlFetchInt::parse(p))
#undef FAIL
{}

void validatorSession_blockUpdate::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ts_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(actions_, s);
  TlStoreBinary::store(state_, s);
}

void validatorSession_blockUpdate::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(ts_, s);
  TlStoreVector<TlStoreBoxedUnknown<TlStoreObject>>::store(actions_, s);
  TlStoreBinary::store(state_, s);
}

void validatorSession_blockUpdate::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_blockUpdate");
    s.store_field("ts", ts_);
    { const std::vector<object_storage<validatorSession_round_Message>> &v = actions_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("actions", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { if (v[i] == nullptr) { s.store_field("", "null"); } else { v[i]->store(s, ""); } } s.store_class_end(); }
    s.store_field("state", state_);
    s.store_class_end();
  }
}

validatorSession_candidate::validatorSession_candidate()
  : src_()
  , round_()
  , root_hash_()
  , data_()
  , collated_data_()
{}

validatorSession_candidate::validatorSession_candidate(td::UInt256 const &src_, std::int32_t round_, td::UInt256 const &root_hash_, td::BufferSlice &&data_, td::BufferSlice &&collated_data_)
  : src_(src_)
  , round_(round_)
  , root_hash_(root_hash_)
  , data_(std::move(data_))
  , collated_data_(std::move(collated_data_))
{}

const std::int32_t validatorSession_candidate::ID;

validatorSession_candidate::validatorSession_candidate(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : src_(TlFetchInt256::parse(p))
  , round_(TlFetchInt::parse(p))
  , root_hash_(TlFetchInt256::parse(p))
  , data_(TlFetchBytes<td::BufferSlice>::parse(p))
  , collated_data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void validatorSession_candidate::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreString::store(data_, s);
  TlStoreString::store(collated_data_, s);
}

void validatorSession_candidate::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreString::store(data_, s);
  TlStoreString::store(collated_data_, s);
}

void validatorSession_candidate::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_candidate");
    s.store_field("src", src_);
    s.store_field("round", round_);
    s.store_field("root_hash", root_hash_);
    s.store_bytes_field("data", data_);
    s.store_bytes_field("collated_data", collated_data_);
    s.store_class_end();
  }
}

validatorSession_candidateId::validatorSession_candidateId()
  : src_()
  , root_hash_()
  , file_hash_()
  , collated_data_file_hash_()
{}

validatorSession_candidateId::validatorSession_candidateId(td::UInt256 const &src_, td::UInt256 const &root_hash_, td::UInt256 const &file_hash_, td::UInt256 const &collated_data_file_hash_)
  : src_(src_)
  , root_hash_(root_hash_)
  , file_hash_(file_hash_)
  , collated_data_file_hash_(collated_data_file_hash_)
{}

const std::int32_t validatorSession_candidateId::ID;

validatorSession_candidateId::validatorSession_candidateId(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : src_(TlFetchInt256::parse(p))
  , root_hash_(TlFetchInt256::parse(p))
  , file_hash_(TlFetchInt256::parse(p))
  , collated_data_file_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void validatorSession_candidateId::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreBinary::store(collated_data_file_hash_, s);
}

void validatorSession_candidateId::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(src_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreBinary::store(collated_data_file_hash_, s);
}

void validatorSession_candidateId::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_candidateId");
    s.store_field("src", src_);
    s.store_field("root_hash", root_hash_);
    s.store_field("file_hash", file_hash_);
    s.store_field("collated_data_file_hash", collated_data_file_hash_);
    s.store_class_end();
  }
}

validatorSession_id::validatorSession_id()
  : slice_()
  , start_time_()
  , end_time_()
  , participants_()
{}

validatorSession_id::validatorSession_id(td::UInt256 const &slice_, std::int32_t start_time_, std::int32_t end_time_, std::vector<td::UInt256> &&participants_)
  : slice_(slice_)
  , start_time_(start_time_)
  , end_time_(end_time_)
  , participants_(std::move(participants_))
{}

const std::int32_t validatorSession_id::ID;

validatorSession_id::validatorSession_id(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : slice_(TlFetchInt256::parse(p))
  , start_time_(TlFetchInt::parse(p))
  , end_time_(TlFetchInt::parse(p))
  , participants_(TlFetchVector<TlFetchInt256>::parse(p))
#undef FAIL
{}

void validatorSession_id::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(slice_, s);
  TlStoreBinary::store(start_time_, s);
  TlStoreBinary::store(end_time_, s);
  TlStoreVector<TlStoreBinary>::store(participants_, s);
}

void validatorSession_id::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(slice_, s);
  TlStoreBinary::store(start_time_, s);
  TlStoreBinary::store(end_time_, s);
  TlStoreVector<TlStoreBinary>::store(participants_, s);
}

void validatorSession_id::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_id");
    s.store_field("slice", slice_);
    s.store_field("start_time", start_time_);
    s.store_field("end_time", end_time_);
    { const std::vector<td::UInt256> &v = participants_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("participants", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

object_storage<validatorSession_Message> validatorSession_Message::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case validatorSession_message_startSession::ID:
      return validatorSession_message_startSession::fetch(p);
    case validatorSession_message_finishSession::ID:
      return validatorSession_message_finishSession::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

validatorSession_message_startSession::validatorSession_message_startSession() {
}

const std::int32_t validatorSession_message_startSession::ID;

validatorSession_message_startSession::validatorSession_message_startSession(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void validatorSession_message_startSession::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void validatorSession_message_startSession::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void validatorSession_message_startSession::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_startSession");
    s.store_class_end();
  }
}

validatorSession_message_finishSession::validatorSession_message_finishSession() {
}

const std::int32_t validatorSession_message_finishSession::ID;

validatorSession_message_finishSession::validatorSession_message_finishSession(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void validatorSession_message_finishSession::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
}

void validatorSession_message_finishSession::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
}

void validatorSession_message_finishSession::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_finishSession");
    s.store_class_end();
  }
}

validatorSession_pong::validatorSession_pong()
  : hash_()
{}

validatorSession_pong::validatorSession_pong(std::int64_t hash_)
  : hash_(hash_)
{}

const std::int32_t validatorSession_pong::ID;

validatorSession_pong::validatorSession_pong(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchLong::parse(p))
#undef FAIL
{}

void validatorSession_pong::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
}

void validatorSession_pong::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(hash_, s);
}

void validatorSession_pong::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_pong");
    s.store_field("hash", hash_);
    s.store_class_end();
  }
}

validatorSession_round_id::validatorSession_round_id()
  : session_()
  , height_()
  , prev_block_()
  , seqno_()
{}

validatorSession_round_id::validatorSession_round_id(td::UInt256 const &session_, std::int64_t height_, td::UInt256 const &prev_block_, std::int32_t seqno_)
  : session_(session_)
  , height_(height_)
  , prev_block_(prev_block_)
  , seqno_(seqno_)
{}

const std::int32_t validatorSession_round_id::ID;

validatorSession_round_id::validatorSession_round_id(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : session_(TlFetchInt256::parse(p))
  , height_(TlFetchLong::parse(p))
  , prev_block_(TlFetchInt256::parse(p))
  , seqno_(TlFetchInt::parse(p))
#undef FAIL
{}

void validatorSession_round_id::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(session_, s);
  TlStoreBinary::store(height_, s);
  TlStoreBinary::store(prev_block_, s);
  TlStoreBinary::store(seqno_, s);
}

void validatorSession_round_id::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(session_, s);
  TlStoreBinary::store(height_, s);
  TlStoreBinary::store(prev_block_, s);
  TlStoreBinary::store(seqno_, s);
}

void validatorSession_round_id::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_round_id");
    s.store_field("session", session_);
    s.store_field("height", height_);
    s.store_field("prev_block", prev_block_);
    s.store_field("seqno", seqno_);
    s.store_class_end();
  }
}

object_storage<validatorSession_round_Message> validatorSession_round_Message::fetch(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return nullptr;
  int constructor = p.fetch_int();
  switch (constructor) {
    case validatorSession_message_submittedBlock::ID:
      return validatorSession_message_submittedBlock::fetch(p);
    case validatorSession_message_approvedBlock::ID:
      return validatorSession_message_approvedBlock::fetch(p);
    case validatorSession_message_commit::ID:
      return validatorSession_message_commit::fetch(p);
    case validatorSession_message_vote::ID:
      return validatorSession_message_vote::fetch(p);
    case validatorSession_message_precommit::ID:
      return validatorSession_message_precommit::fetch(p);
    case validatorSession_message_empty::ID:
      return validatorSession_message_empty::fetch(p);
    default:
      FAIL(PSTRING() << "Unknown constructor found " << td::format::as_hex(constructor));
  }
#undef FAIL
}

validatorSession_message_submittedBlock::validatorSession_message_submittedBlock()
  : round_()
  , root_hash_()
  , file_hash_()
  , collated_data_file_hash_()
{}

validatorSession_message_submittedBlock::validatorSession_message_submittedBlock(std::int32_t round_, td::UInt256 const &root_hash_, td::UInt256 const &file_hash_, td::UInt256 const &collated_data_file_hash_)
  : round_(round_)
  , root_hash_(root_hash_)
  , file_hash_(file_hash_)
  , collated_data_file_hash_(collated_data_file_hash_)
{}

const std::int32_t validatorSession_message_submittedBlock::ID;

validatorSession_message_submittedBlock::validatorSession_message_submittedBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt::parse(p))
  , root_hash_(TlFetchInt256::parse(p))
  , file_hash_(TlFetchInt256::parse(p))
  , collated_data_file_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void validatorSession_message_submittedBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreBinary::store(collated_data_file_hash_, s);
}

void validatorSession_message_submittedBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(root_hash_, s);
  TlStoreBinary::store(file_hash_, s);
  TlStoreBinary::store(collated_data_file_hash_, s);
}

void validatorSession_message_submittedBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_submittedBlock");
    s.store_field("round", round_);
    s.store_field("root_hash", root_hash_);
    s.store_field("file_hash", file_hash_);
    s.store_field("collated_data_file_hash", collated_data_file_hash_);
    s.store_class_end();
  }
}

validatorSession_message_approvedBlock::validatorSession_message_approvedBlock()
  : round_()
  , candidate_()
{}

validatorSession_message_approvedBlock::validatorSession_message_approvedBlock(std::int32_t round_, td::UInt256 const &candidate_)
  : round_(round_)
  , candidate_(candidate_)
{}

const std::int32_t validatorSession_message_approvedBlock::ID;

validatorSession_message_approvedBlock::validatorSession_message_approvedBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt::parse(p))
  , candidate_(TlFetchInt256::parse(p))
#undef FAIL
{}

void validatorSession_message_approvedBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(candidate_, s);
}

void validatorSession_message_approvedBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(candidate_, s);
}

void validatorSession_message_approvedBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_approvedBlock");
    s.store_field("round", round_);
    s.store_field("candidate", candidate_);
    s.store_class_end();
  }
}

validatorSession_message_commit::validatorSession_message_commit()
  : round_()
  , candidate_()
  , signature_()
{}

validatorSession_message_commit::validatorSession_message_commit(std::int32_t round_, td::UInt256 const &candidate_, td::BufferSlice &&signature_)
  : round_(round_)
  , candidate_(candidate_)
  , signature_(std::move(signature_))
{}

const std::int32_t validatorSession_message_commit::ID;

validatorSession_message_commit::validatorSession_message_commit(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt::parse(p))
  , candidate_(TlFetchInt256::parse(p))
  , signature_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void validatorSession_message_commit::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(candidate_, s);
  TlStoreString::store(signature_, s);
}

void validatorSession_message_commit::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(candidate_, s);
  TlStoreString::store(signature_, s);
}

void validatorSession_message_commit::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_commit");
    s.store_field("round", round_);
    s.store_field("candidate", candidate_);
    s.store_bytes_field("signature", signature_);
    s.store_class_end();
  }
}

validatorSession_message_vote::validatorSession_message_vote()
  : round_()
  , attempt_()
  , candidate_()
{}

validatorSession_message_vote::validatorSession_message_vote(std::int32_t round_, std::int32_t attempt_, td::UInt256 const &candidate_)
  : round_(round_)
  , attempt_(attempt_)
  , candidate_(candidate_)
{}

const std::int32_t validatorSession_message_vote::ID;

validatorSession_message_vote::validatorSession_message_vote(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt::parse(p))
  , attempt_(TlFetchInt::parse(p))
  , candidate_(TlFetchInt256::parse(p))
#undef FAIL
{}

void validatorSession_message_vote::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(attempt_, s);
  TlStoreBinary::store(candidate_, s);
}

void validatorSession_message_vote::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(attempt_, s);
  TlStoreBinary::store(candidate_, s);
}

void validatorSession_message_vote::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_vote");
    s.store_field("round", round_);
    s.store_field("attempt", attempt_);
    s.store_field("candidate", candidate_);
    s.store_class_end();
  }
}

validatorSession_message_precommit::validatorSession_message_precommit()
  : round_()
  , attempt_()
  , candidate_()
{}

validatorSession_message_precommit::validatorSession_message_precommit(std::int32_t round_, std::int32_t attempt_, td::UInt256 const &candidate_)
  : round_(round_)
  , attempt_(attempt_)
  , candidate_(candidate_)
{}

const std::int32_t validatorSession_message_precommit::ID;

validatorSession_message_precommit::validatorSession_message_precommit(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt::parse(p))
  , attempt_(TlFetchInt::parse(p))
  , candidate_(TlFetchInt256::parse(p))
#undef FAIL
{}

void validatorSession_message_precommit::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(attempt_, s);
  TlStoreBinary::store(candidate_, s);
}

void validatorSession_message_precommit::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(attempt_, s);
  TlStoreBinary::store(candidate_, s);
}

void validatorSession_message_precommit::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_precommit");
    s.store_field("round", round_);
    s.store_field("attempt", attempt_);
    s.store_field("candidate", candidate_);
    s.store_class_end();
  }
}

validatorSession_message_empty::validatorSession_message_empty()
  : round_()
  , attempt_()
{}

validatorSession_message_empty::validatorSession_message_empty(std::int32_t round_, std::int32_t attempt_)
  : round_(round_)
  , attempt_(attempt_)
{}

const std::int32_t validatorSession_message_empty::ID;

validatorSession_message_empty::validatorSession_message_empty(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt::parse(p))
  , attempt_(TlFetchInt::parse(p))
#undef FAIL
{}

void validatorSession_message_empty::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(attempt_, s);
}

void validatorSession_message_empty::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(attempt_, s);
}

void validatorSession_message_empty::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_message_empty");
    s.store_field("round", round_);
    s.store_field("attempt", attempt_);
    s.store_class_end();
  }
}

validatorSession_candidate_id::validatorSession_candidate_id()
  : round_()
  , block_hash_()
{}

validatorSession_candidate_id::validatorSession_candidate_id(td::UInt256 const &round_, td::UInt256 const &block_hash_)
  : round_(round_)
  , block_hash_(block_hash_)
{}

const std::int32_t validatorSession_candidate_id::ID;

validatorSession_candidate_id::validatorSession_candidate_id(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt256::parse(p))
  , block_hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void validatorSession_candidate_id::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(block_hash_, s);
}

void validatorSession_candidate_id::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  TlStoreBinary::store(round_, s);
  TlStoreBinary::store(block_hash_, s);
}

void validatorSession_candidate_id::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_candidate_id");
    s.store_field("round", round_);
    s.store_field("block_hash", block_hash_);
    s.store_class_end();
  }
}

catchain_getBlock::catchain_getBlock()
  : block_()
{}

catchain_getBlock::catchain_getBlock(td::UInt256 const &block_)
  : block_(block_)
{}

const std::int32_t catchain_getBlock::ID;

catchain_getBlock::catchain_getBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchInt256::parse(p))
#undef FAIL
{}

void catchain_getBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(155049336);
  TlStoreBinary::store(block_, s);
}

void catchain_getBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(155049336);
  TlStoreBinary::store(block_, s);
}

void catchain_getBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_getBlock");
    s.store_field("block", block_);
    s.store_class_end();
  }
}

catchain_getBlock::ReturnType catchain_getBlock::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<catchain_BlockResult>::parse(p);
#undef FAIL
}

catchain_getBlockHistory::catchain_getBlockHistory()
  : block_()
  , height_()
  , stop_if_()
{}

catchain_getBlockHistory::catchain_getBlockHistory(td::UInt256 const &block_, std::int64_t height_, std::vector<td::UInt256> &&stop_if_)
  : block_(block_)
  , height_(height_)
  , stop_if_(std::move(stop_if_))
{}

const std::int32_t catchain_getBlockHistory::ID;

catchain_getBlockHistory::catchain_getBlockHistory(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchInt256::parse(p))
  , height_(TlFetchLong::parse(p))
  , stop_if_(TlFetchVector<TlFetchInt256>::parse(p))
#undef FAIL
{}

void catchain_getBlockHistory::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-1470730762);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(height_, s);
  TlStoreVector<TlStoreBinary>::store(stop_if_, s);
}

void catchain_getBlockHistory::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-1470730762);
  TlStoreBinary::store(block_, s);
  TlStoreBinary::store(height_, s);
  TlStoreVector<TlStoreBinary>::store(stop_if_, s);
}

void catchain_getBlockHistory::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_getBlockHistory");
    s.store_field("block", block_);
    s.store_field("height", height_);
    { const std::vector<td::UInt256> &v = stop_if_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("stop_if", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_getBlockHistory::ReturnType catchain_getBlockHistory::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<catchain_sent>, -84454993>::parse(p);
#undef FAIL
}

catchain_getBlocks::catchain_getBlocks()
  : blocks_()
{}

catchain_getBlocks::catchain_getBlocks(std::vector<td::UInt256> &&blocks_)
  : blocks_(std::move(blocks_))
{}

const std::int32_t catchain_getBlocks::ID;

catchain_getBlocks::catchain_getBlocks(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : blocks_(TlFetchVector<TlFetchInt256>::parse(p))
#undef FAIL
{}

void catchain_getBlocks::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(53062594);
  TlStoreVector<TlStoreBinary>::store(blocks_, s);
}

void catchain_getBlocks::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(53062594);
  TlStoreVector<TlStoreBinary>::store(blocks_, s);
}

void catchain_getBlocks::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_getBlocks");
    { const std::vector<td::UInt256> &v = blocks_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("blocks", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_getBlocks::ReturnType catchain_getBlocks::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<catchain_sent>, -84454993>::parse(p);
#undef FAIL
}

catchain_getDifference::catchain_getDifference()
  : rt_()
{}

catchain_getDifference::catchain_getDifference(std::vector<std::int32_t> &&rt_)
  : rt_(std::move(rt_))
{}

const std::int32_t catchain_getDifference::ID;

catchain_getDifference::catchain_getDifference(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : rt_(TlFetchVector<TlFetchInt>::parse(p))
#undef FAIL
{}

void catchain_getDifference::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-798175528);
  TlStoreVector<TlStoreBinary>::store(rt_, s);
}

void catchain_getDifference::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-798175528);
  TlStoreVector<TlStoreBinary>::store(rt_, s);
}

void catchain_getDifference::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "catchain_getDifference");
    { const std::vector<std::int32_t> &v = rt_; const std::uint32_t multiplicity = static_cast<std::uint32_t>(v.size()); const std::string vector_name = "vector[" + td::to_string(multiplicity)+ "]"; s.store_class_begin("rt", vector_name.c_str()); for (std::uint32_t i = 0; i < multiplicity; i++) { s.store_field("", v[i]); } s.store_class_end(); }
    s.store_class_end();
  }
}

catchain_getDifference::ReturnType catchain_getDifference::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<catchain_Difference>::parse(p);
#undef FAIL
}

dht_findNode::dht_findNode()
  : key_()
  , k_()
{}

dht_findNode::dht_findNode(td::UInt256 const &key_, std::int32_t k_)
  : key_(key_)
  , k_(k_)
{}

const std::int32_t dht_findNode::ID;

dht_findNode::dht_findNode(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
  , k_(TlFetchInt::parse(p))
#undef FAIL
{}

void dht_findNode::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1826803307);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(k_, s);
}

void dht_findNode::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1826803307);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(k_, s);
}

void dht_findNode::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_findNode");
    s.store_field("key", key_);
    s.store_field("k", k_);
    s.store_class_end();
  }
}

dht_findNode::ReturnType dht_findNode::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<dht_nodes>, 2037686462>::parse(p);
#undef FAIL
}

dht_findValue::dht_findValue()
  : key_()
  , k_()
{}

dht_findValue::dht_findValue(td::UInt256 const &key_, std::int32_t k_)
  : key_(key_)
  , k_(k_)
{}

const std::int32_t dht_findValue::ID;

dht_findValue::dht_findValue(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : key_(TlFetchInt256::parse(p))
  , k_(TlFetchInt::parse(p))
#undef FAIL
{}

void dht_findValue::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-1370791919);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(k_, s);
}

void dht_findValue::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-1370791919);
  TlStoreBinary::store(key_, s);
  TlStoreBinary::store(k_, s);
}

void dht_findValue::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_findValue");
    s.store_field("key", key_);
    s.store_field("k", k_);
    s.store_class_end();
  }
}

dht_findValue::ReturnType dht_findValue::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<dht_ValueResult>::parse(p);
#undef FAIL
}

dht_getSignedAddressList::dht_getSignedAddressList() {
}

const std::int32_t dht_getSignedAddressList::ID;

dht_getSignedAddressList::dht_getSignedAddressList(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void dht_getSignedAddressList::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(960283782);
}

void dht_getSignedAddressList::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(960283782);
}

void dht_getSignedAddressList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_getSignedAddressList");
    s.store_class_end();
  }
}

dht_getSignedAddressList::ReturnType dht_getSignedAddressList::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<adnl_node>, 620296016>::parse(p);
#undef FAIL
}

dht_ping::dht_ping()
  : random_id_()
{}

dht_ping::dht_ping(std::int64_t random_id_)
  : random_id_(random_id_)
{}

const std::int32_t dht_ping::ID;

dht_ping::dht_ping(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : random_id_(TlFetchLong::parse(p))
#undef FAIL
{}

void dht_ping::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-873775336);
  TlStoreBinary::store(random_id_, s);
}

void dht_ping::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-873775336);
  TlStoreBinary::store(random_id_, s);
}

void dht_ping::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_ping");
    s.store_field("random_id", random_id_);
    s.store_class_end();
  }
}

dht_ping::ReturnType dht_ping::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<dht_pong>, 1519054721>::parse(p);
#undef FAIL
}

dht_query::dht_query()
  : node_()
{}

dht_query::dht_query(object_storage<dht_node> &&node_)
  : node_(std::move(node_))
{}

const std::int32_t dht_query::ID;

dht_query::dht_query(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : node_(TlFetchObject<dht_node>::parse(p))
#undef FAIL
{}

void dht_query::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(2102593385);
  TlStoreObject::store(node_, s);
}

void dht_query::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(2102593385);
  TlStoreObject::store(node_, s);
}

void dht_query::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_query");
    if (node_ == nullptr) { s.store_field("node", "null"); } else { node_->store(s, "node"); }
    s.store_class_end();
  }
}

dht_query::ReturnType dht_query::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchTrue, 1072550713>::parse(p);
#undef FAIL
}

dht_store::dht_store()
  : value_()
{}

dht_store::dht_store(object_storage<dht_value> &&value_)
  : value_(std::move(value_))
{}

const std::int32_t dht_store::ID;

dht_store::dht_store(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : value_(TlFetchObject<dht_value>::parse(p))
#undef FAIL
{}

void dht_store::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(882065938);
  TlStoreObject::store(value_, s);
}

void dht_store::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(882065938);
  TlStoreObject::store(value_, s);
}

void dht_store::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "dht_store");
    if (value_ == nullptr) { s.store_field("value", "null"); } else { value_->store(s, "value"); }
    s.store_class_end();
  }
}

dht_store::ReturnType dht_store::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<dht_stored>, 1881602824>::parse(p);
#undef FAIL
}

getTestObject::getTestObject() {
}

const std::int32_t getTestObject::ID;

getTestObject::getTestObject(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void getTestObject::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(197109379);
}

void getTestObject::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(197109379);
}

void getTestObject::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "getTestObject");
    s.store_class_end();
  }
}

getTestObject::ReturnType getTestObject::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<TestObject>::parse(p);
#undef FAIL
}

liteServer_debug_setVerbosity::liteServer_debug_setVerbosity()
  : verbosity_()
{}

liteServer_debug_setVerbosity::liteServer_debug_setVerbosity(object_storage<liteServer_debug_verbosity> &&verbosity_)
  : verbosity_(std::move(verbosity_))
{}

const std::int32_t liteServer_debug_setVerbosity::ID;

liteServer_debug_setVerbosity::liteServer_debug_setVerbosity(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : verbosity_(TlFetchObject<liteServer_debug_verbosity>::parse(p))
#undef FAIL
{}

void liteServer_debug_setVerbosity::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(462775286);
  TlStoreObject::store(verbosity_, s);
}

void liteServer_debug_setVerbosity::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(462775286);
  TlStoreObject::store(verbosity_, s);
}

void liteServer_debug_setVerbosity::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_debug_setVerbosity");
    if (verbosity_ == nullptr) { s.store_field("verbosity", "null"); } else { verbosity_->store(s, "verbosity"); }
    s.store_class_end();
  }
}

liteServer_debug_setVerbosity::ReturnType liteServer_debug_setVerbosity::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<liteServer_debug_verbosity>, 1564493619>::parse(p);
#undef FAIL
}

liteServer_getAccountState::liteServer_getAccountState()
  : id_()
  , account_()
{}

liteServer_getAccountState::liteServer_getAccountState(object_storage<tonNode_blockIdExt> &&id_, object_storage<liteServer_accountId> &&account_)
  : id_(std::move(id_))
  , account_(std::move(account_))
{}

const std::int32_t liteServer_getAccountState::ID;

liteServer_getAccountState::liteServer_getAccountState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , account_(TlFetchObject<liteServer_accountId>::parse(p))
#undef FAIL
{}

void liteServer_getAccountState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1804144165);
  TlStoreObject::store(id_, s);
  TlStoreObject::store(account_, s);
}

void liteServer_getAccountState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1804144165);
  TlStoreObject::store(id_, s);
  TlStoreObject::store(account_, s);
}

void liteServer_getAccountState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_getAccountState");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    if (account_ == nullptr) { s.store_field("account", "null"); } else { account_->store(s, "account"); }
    s.store_class_end();
  }
}

liteServer_getAccountState::ReturnType liteServer_getAccountState::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<liteServer_accountState>, 1887029073>::parse(p);
#undef FAIL
}

liteServer_getBlock::liteServer_getBlock()
  : id_()
{}

liteServer_getBlock::liteServer_getBlock(object_storage<tonNode_blockIdExt> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t liteServer_getBlock::ID;

liteServer_getBlock::liteServer_getBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void liteServer_getBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1668796173);
  TlStoreObject::store(id_, s);
}

void liteServer_getBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1668796173);
  TlStoreObject::store(id_, s);
}

void liteServer_getBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_getBlock");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

liteServer_getBlock::ReturnType liteServer_getBlock::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<liteServer_blockData>, -1519063700>::parse(p);
#undef FAIL
}

liteServer_getMasterchainInfo::liteServer_getMasterchainInfo() {
}

const std::int32_t liteServer_getMasterchainInfo::ID;

liteServer_getMasterchainInfo::liteServer_getMasterchainInfo(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void liteServer_getMasterchainInfo::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-1984567762);
}

void liteServer_getMasterchainInfo::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-1984567762);
}

void liteServer_getMasterchainInfo::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_getMasterchainInfo");
    s.store_class_end();
  }
}

liteServer_getMasterchainInfo::ReturnType liteServer_getMasterchainInfo::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<liteServer_masterchainInfo>, -2055001983>::parse(p);
#undef FAIL
}

liteServer_getState::liteServer_getState()
  : id_()
{}

liteServer_getState::liteServer_getState(object_storage<tonNode_blockIdExt> &&id_)
  : id_(std::move(id_))
{}

const std::int32_t liteServer_getState::ID;

liteServer_getState::liteServer_getState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : id_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void liteServer_getState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-1167184202);
  TlStoreObject::store(id_, s);
}

void liteServer_getState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-1167184202);
  TlStoreObject::store(id_, s);
}

void liteServer_getState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_getState");
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

liteServer_getState::ReturnType liteServer_getState::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<liteServer_blockState>, -1414669300>::parse(p);
#undef FAIL
}

liteServer_getTime::liteServer_getTime() {
}

const std::int32_t liteServer_getTime::ID;

liteServer_getTime::liteServer_getTime(td::TlParser &p)
#define FAIL(error) p.set_error(error)
#undef FAIL
{
  (void)p;
}

void liteServer_getTime::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(380459572);
}

void liteServer_getTime::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(380459572);
}

void liteServer_getTime::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_getTime");
    s.store_class_end();
  }
}

liteServer_getTime::ReturnType liteServer_getTime::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<liteServer_currentTime>, -380436467>::parse(p);
#undef FAIL
}

liteServer_query::liteServer_query()
  : data_()
{}

liteServer_query::liteServer_query(td::BufferSlice &&data_)
  : data_(std::move(data_))
{}

const std::int32_t liteServer_query::ID;

liteServer_query::liteServer_query(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : data_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void liteServer_query::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(2039219935);
  TlStoreString::store(data_, s);
}

void liteServer_query::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(2039219935);
  TlStoreString::store(data_, s);
}

void liteServer_query::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_query");
    s.store_bytes_field("data", data_);
    s.store_class_end();
  }
}

liteServer_query::ReturnType liteServer_query::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<Object>, 695225504>::parse(p);
#undef FAIL
}

liteServer_sendMessage::liteServer_sendMessage()
  : body_()
{}

liteServer_sendMessage::liteServer_sendMessage(td::BufferSlice &&body_)
  : body_(std::move(body_))
{}

const std::int32_t liteServer_sendMessage::ID;

liteServer_sendMessage::liteServer_sendMessage(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : body_(TlFetchBytes<td::BufferSlice>::parse(p))
#undef FAIL
{}

void liteServer_sendMessage::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1762317442);
  TlStoreString::store(body_, s);
}

void liteServer_sendMessage::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1762317442);
  TlStoreString::store(body_, s);
}

void liteServer_sendMessage::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "liteServer_sendMessage");
    s.store_bytes_field("body", body_);
    s.store_class_end();
  }
}

liteServer_sendMessage::ReturnType liteServer_sendMessage::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<liteServer_sendMsgStatus>, 961602967>::parse(p);
#undef FAIL
}

overlay_getBroadcast::overlay_getBroadcast()
  : hash_()
{}

overlay_getBroadcast::overlay_getBroadcast(td::UInt256 const &hash_)
  : hash_(hash_)
{}

const std::int32_t overlay_getBroadcast::ID;

overlay_getBroadcast::overlay_getBroadcast(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchInt256::parse(p))
#undef FAIL
{}

void overlay_getBroadcast::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(758510240);
  TlStoreBinary::store(hash_, s);
}

void overlay_getBroadcast::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(758510240);
  TlStoreBinary::store(hash_, s);
}

void overlay_getBroadcast::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_getBroadcast");
    s.store_field("hash", hash_);
    s.store_class_end();
  }
}

overlay_getBroadcast::ReturnType overlay_getBroadcast::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<overlay_Broadcast>::parse(p);
#undef FAIL
}

overlay_getBroadcastList::overlay_getBroadcastList()
  : list_()
{}

overlay_getBroadcastList::overlay_getBroadcastList(object_storage<overlay_broadcastList> &&list_)
  : list_(std::move(list_))
{}

const std::int32_t overlay_getBroadcastList::ID;

overlay_getBroadcastList::overlay_getBroadcastList(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : list_(TlFetchObject<overlay_broadcastList>::parse(p))
#undef FAIL
{}

void overlay_getBroadcastList::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1109141562);
  TlStoreObject::store(list_, s);
}

void overlay_getBroadcastList::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1109141562);
  TlStoreObject::store(list_, s);
}

void overlay_getBroadcastList::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_getBroadcastList");
    if (list_ == nullptr) { s.store_field("list", "null"); } else { list_->store(s, "list"); }
    s.store_class_end();
  }
}

overlay_getBroadcastList::ReturnType overlay_getBroadcastList::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<overlay_broadcastList>, 416407263>::parse(p);
#undef FAIL
}

overlay_getRandomPeers::overlay_getRandomPeers()
  : peers_()
{}

overlay_getRandomPeers::overlay_getRandomPeers(object_storage<overlay_nodes> &&peers_)
  : peers_(std::move(peers_))
{}

const std::int32_t overlay_getRandomPeers::ID;

overlay_getRandomPeers::overlay_getRandomPeers(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : peers_(TlFetchObject<overlay_nodes>::parse(p))
#undef FAIL
{}

void overlay_getRandomPeers::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1223582891);
  TlStoreObject::store(peers_, s);
}

void overlay_getRandomPeers::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1223582891);
  TlStoreObject::store(peers_, s);
}

void overlay_getRandomPeers::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_getRandomPeers");
    if (peers_ == nullptr) { s.store_field("peers", "null"); } else { peers_->store(s, "peers"); }
    s.store_class_end();
  }
}

overlay_getRandomPeers::ReturnType overlay_getRandomPeers::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<overlay_nodes>, -460904178>::parse(p);
#undef FAIL
}

overlay_query::overlay_query()
  : overlay_()
{}

overlay_query::overlay_query(td::UInt256 const &overlay_)
  : overlay_(overlay_)
{}

const std::int32_t overlay_query::ID;

overlay_query::overlay_query(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : overlay_(TlFetchInt256::parse(p))
#undef FAIL
{}

void overlay_query::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-855800765);
  TlStoreBinary::store(overlay_, s);
}

void overlay_query::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-855800765);
  TlStoreBinary::store(overlay_, s);
}

void overlay_query::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "overlay_query");
    s.store_field("overlay", overlay_);
    s.store_class_end();
  }
}

overlay_query::ReturnType overlay_query::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchTrue, 1072550713>::parse(p);
#undef FAIL
}

tcp_ping::tcp_ping()
  : random_id_()
{}

tcp_ping::tcp_ping(std::int64_t random_id_)
  : random_id_(random_id_)
{}

const std::int32_t tcp_ping::ID;

tcp_ping::tcp_ping(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : random_id_(TlFetchLong::parse(p))
#undef FAIL
{}

void tcp_ping::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1292381082);
  TlStoreBinary::store(random_id_, s);
}

void tcp_ping::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1292381082);
  TlStoreBinary::store(random_id_, s);
}

void tcp_ping::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tcp_ping");
    s.store_field("random_id", random_id_);
    s.store_class_end();
  }
}

tcp_ping::ReturnType tcp_ping::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<tcp_pong>, -597034237>::parse(p);
#undef FAIL
}

tonNode_downloadBlock::tonNode_downloadBlock()
  : block_()
{}

tonNode_downloadBlock::tonNode_downloadBlock(object_storage<tonNode_blockIdExt> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t tonNode_downloadBlock::ID;

tonNode_downloadBlock::tonNode_downloadBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_downloadBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-495814205);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-495814205);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_downloadBlock");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

tonNode_downloadBlock::ReturnType tonNode_downloadBlock::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<tonNode_data>, 1443505284>::parse(p);
#undef FAIL
}

tonNode_downloadBlockProof::tonNode_downloadBlockProof()
  : block_()
{}

tonNode_downloadBlockProof::tonNode_downloadBlockProof(object_storage<tonNode_blockIdExt> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t tonNode_downloadBlockProof::ID;

tonNode_downloadBlockProof::tonNode_downloadBlockProof(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_downloadBlockProof::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1272334218);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadBlockProof::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1272334218);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadBlockProof::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_downloadBlockProof");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

tonNode_downloadBlockProof::ReturnType tonNode_downloadBlockProof::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<tonNode_data>, 1443505284>::parse(p);
#undef FAIL
}

tonNode_downloadBlockProofLink::tonNode_downloadBlockProofLink()
  : block_()
{}

tonNode_downloadBlockProofLink::tonNode_downloadBlockProofLink(object_storage<tonNode_blockIdExt> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t tonNode_downloadBlockProofLink::ID;

tonNode_downloadBlockProofLink::tonNode_downloadBlockProofLink(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_downloadBlockProofLink::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(632488134);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadBlockProofLink::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(632488134);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadBlockProofLink::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_downloadBlockProofLink");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

tonNode_downloadBlockProofLink::ReturnType tonNode_downloadBlockProofLink::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<tonNode_data>, 1443505284>::parse(p);
#undef FAIL
}

tonNode_downloadState::tonNode_downloadState()
  : block_()
{}

tonNode_downloadState::tonNode_downloadState(object_storage<tonNode_blockIdExt> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t tonNode_downloadState::ID;

tonNode_downloadState::tonNode_downloadState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_downloadState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-738248612);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-738248612);
  TlStoreObject::store(block_, s);
}

void tonNode_downloadState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_downloadState");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

tonNode_downloadState::ReturnType tonNode_downloadState::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<tonNode_data>, 1443505284>::parse(p);
#undef FAIL
}

tonNode_getNextBlockDescription::tonNode_getNextBlockDescription()
  : prev_block_()
{}

tonNode_getNextBlockDescription::tonNode_getNextBlockDescription(object_storage<tonNode_blockIdExt> &&prev_block_)
  : prev_block_(std::move(prev_block_))
{}

const std::int32_t tonNode_getNextBlockDescription::ID;

tonNode_getNextBlockDescription::tonNode_getNextBlockDescription(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : prev_block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_getNextBlockDescription::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(341160179);
  TlStoreObject::store(prev_block_, s);
}

void tonNode_getNextBlockDescription::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(341160179);
  TlStoreObject::store(prev_block_, s);
}

void tonNode_getNextBlockDescription::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_getNextBlockDescription");
    if (prev_block_ == nullptr) { s.store_field("prev_block", "null"); } else { prev_block_->store(s, "prev_block"); }
    s.store_class_end();
  }
}

tonNode_getNextBlockDescription::ReturnType tonNode_getNextBlockDescription::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<tonNode_BlockDescription>::parse(p);
#undef FAIL
}

tonNode_prepareBlock::tonNode_prepareBlock()
  : block_()
{}

tonNode_prepareBlock::tonNode_prepareBlock(object_storage<tonNode_blockIdExt> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t tonNode_prepareBlock::ID;

tonNode_prepareBlock::tonNode_prepareBlock(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_prepareBlock::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1973649230);
  TlStoreObject::store(block_, s);
}

void tonNode_prepareBlock::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1973649230);
  TlStoreObject::store(block_, s);
}

void tonNode_prepareBlock::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_prepareBlock");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

tonNode_prepareBlock::ReturnType tonNode_prepareBlock::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<tonNode_Prepared>::parse(p);
#undef FAIL
}

tonNode_prepareBlockProof::tonNode_prepareBlockProof()
  : block_()
  , allow_partial_()
{}

tonNode_prepareBlockProof::tonNode_prepareBlockProof(object_storage<tonNode_blockIdExt> &&block_, bool allow_partial_)
  : block_(std::move(block_))
  , allow_partial_(allow_partial_)
{}

const std::int32_t tonNode_prepareBlockProof::ID;

tonNode_prepareBlockProof::tonNode_prepareBlockProof(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
  , allow_partial_(TlFetchBool::parse(p))
#undef FAIL
{}

void tonNode_prepareBlockProof::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-2024000760);
  TlStoreObject::store(block_, s);
  TlStoreBool::store(allow_partial_, s);
}

void tonNode_prepareBlockProof::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-2024000760);
  TlStoreObject::store(block_, s);
  TlStoreBool::store(allow_partial_, s);
}

void tonNode_prepareBlockProof::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_prepareBlockProof");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_field("allow_partial", allow_partial_);
    s.store_class_end();
  }
}

tonNode_prepareBlockProof::ReturnType tonNode_prepareBlockProof::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<tonNode_PreparedProof>::parse(p);
#undef FAIL
}

tonNode_prepareState::tonNode_prepareState()
  : block_()
{}

tonNode_prepareState::tonNode_prepareState(object_storage<tonNode_blockIdExt> &&block_)
  : block_(std::move(block_))
{}

const std::int32_t tonNode_prepareState::ID;

tonNode_prepareState::tonNode_prepareState(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : block_(TlFetchObject<tonNode_blockIdExt>::parse(p))
#undef FAIL
{}

void tonNode_prepareState::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-381168335);
  TlStoreObject::store(block_, s);
}

void tonNode_prepareState::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-381168335);
  TlStoreObject::store(block_, s);
}

void tonNode_prepareState::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "tonNode_prepareState");
    if (block_ == nullptr) { s.store_field("block", "null"); } else { block_->store(s, "block"); }
    s.store_class_end();
  }
}

tonNode_prepareState::ReturnType tonNode_prepareState::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchObject<tonNode_PreparedState>::parse(p);
#undef FAIL
}

validatorSession_downloadCandidate::validatorSession_downloadCandidate()
  : round_()
  , id_()
{}

validatorSession_downloadCandidate::validatorSession_downloadCandidate(std::int32_t round_, object_storage<validatorSession_candidateId> &&id_)
  : round_(round_)
  , id_(std::move(id_))
{}

const std::int32_t validatorSession_downloadCandidate::ID;

validatorSession_downloadCandidate::validatorSession_downloadCandidate(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : round_(TlFetchInt::parse(p))
  , id_(TlFetchObject<validatorSession_candidateId>::parse(p))
#undef FAIL
{}

void validatorSession_downloadCandidate::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(-520274443);
  TlStoreBinary::store(round_, s);
  TlStoreObject::store(id_, s);
}

void validatorSession_downloadCandidate::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(-520274443);
  TlStoreBinary::store(round_, s);
  TlStoreObject::store(id_, s);
}

void validatorSession_downloadCandidate::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_downloadCandidate");
    s.store_field("round", round_);
    if (id_ == nullptr) { s.store_field("id", "null"); } else { id_->store(s, "id"); }
    s.store_class_end();
  }
}

validatorSession_downloadCandidate::ReturnType validatorSession_downloadCandidate::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<validatorSession_candidate>, 2100525125>::parse(p);
#undef FAIL
}

validatorSession_ping::validatorSession_ping()
  : hash_()
{}

validatorSession_ping::validatorSession_ping(std::int64_t hash_)
  : hash_(hash_)
{}

const std::int32_t validatorSession_ping::ID;

validatorSession_ping::validatorSession_ping(td::TlParser &p)
#define FAIL(error) p.set_error(error)
  : hash_(TlFetchLong::parse(p))
#undef FAIL
{}

void validatorSession_ping::store(td::TlStorerCalcLength &s) const {
  (void)sizeof(s);
  s.store_binary(1745111469);
  TlStoreBinary::store(hash_, s);
}

void validatorSession_ping::store(td::TlStorerUnsafe &s) const {
  (void)sizeof(s);
  s.store_binary(1745111469);
  TlStoreBinary::store(hash_, s);
}

void validatorSession_ping::store(td::TlStorerToString &s, const char *field_name) const {
  if (!LOG_IS_STRIPPED(ERROR)) {
    s.store_class_begin(field_name, "validatorSession_ping");
    s.store_field("hash", hash_);
    s.store_class_end();
  }
}

validatorSession_ping::ReturnType validatorSession_ping::fetch_result(td::TlParser &p) {
#define FAIL(error) p.set_error(error); return ReturnType()
  return TlFetchBoxed<TlFetchObject<validatorSession_pong>, -590989459>::parse(p);
#undef FAIL
}
}  // namespace ton_api
}  // namespace ton
