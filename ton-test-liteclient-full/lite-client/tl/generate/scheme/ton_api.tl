int ? = Int;
long ? = Long;
double ? = Double;
string ? = String;
object ? = Object;
function ? = Function;
bytes data:string = Bytes;
true = True;
boolTrue = Bool;
boolFalse = Bool;


vector {t:Type} # [ t ] = Vector t;

int128 4*[ int ] = Int128;
int256 8*[ int ] = Int256;

testObject value:int o:object f:function = TestObject;
testString value:string = TestObject;
testInt value:int = TestObject;
testVectorBytes value:(vector bytes) = TestObject;

tcp.pong random_id:long = tcp.Pong;

fer.raptorQ symbol_size:int total_symbols:int total_size:int = fer.Type;
fer.simple symbol_size:int total_symbols:int total_size:int = fer.Type;

---functions---

tcp.ping random_id:long = tcp.Pong;

getTestObject = TestObject;

---types---

adnl.id.short id:int256 = adnl.id.Short;

adnl.id.pk.unenc data:bytes = adnl.id.Pk;
adnl.id.pk.ed25519 key:int256 = adnl.id.Pk;
adnl.id.pk.aes key:int256 = adnl.id.Pk;
adnl.id.pk.overlay name:bytes = adnl.id.Pk;

adnl.id.ed25519 key:int256 = adnl.id.Full;
adnl.id.aes key:int256 = adnl.id.Full;
// test only
// random is used to have different hashes
// of unenc type
adnl.id.unenc data:bytes = adnl.id.Full;
adnl.id.overlay name:bytes = adnl.id.Full;

adnl.address.udp ip:int port:int = adnl.Address;
adnl.address.udp6 ip:int128 port:int = adnl.Address;
adnl.address.tcp ip:int port:int = adnl.Address;
adnl.address.tcp6 ip:int128 port:int = adnl.Address;

adnl.address.tunnel to:adnl.Address tunid:adnl.id.Full = adnl.Address; 

adnl.addressList addrs:(vector adnl.Address) version:int = adnl.AddressList;

adnl.node id:adnl.id.Full addr_list:adnl.addressList signature:bytes = adnl.Node;
adnl.nodes nodes:(vector adnl.node) = adnl.Nodes;

---functions---

---types---

// Header of received packet
// Magic is omitted, encryption mode is determined by dst
adnl.packetHeader.secp256k1 dst:int256 point:int256 = adnl.PacketHeader;
adnl.packetHeader.unenc dst:int256 = adnl.PacketHeader;
adnl.packetHeader.channel dst:int256 hash:int256 = adnl.PacketHeader;

// @rand1      - random padding
// @from       - full sender id
// @from_short - short version of sender id. May be used if recepient
//             knows about sender. But need to be used with caution
// @message    - one encrypted message
// @messages   - multiple encrypted messages
// @address    - list of network addresses. By default if answer in needed it will be sent
//             backwards
// @seqno      - seqno 
// @confirm_seqno
//             - max received seqno confirmation
// @reinit_date
//             - date of new incarnation start 
// @recv_addr_list_version 
//             - last received addr list version
// @signature  - signature of sender
// @rand2      - random padding
adnl.packetContents rand1:bytes flags:# from:flags.0?adnl.id.Full from_short:flags.1?adnl.id.short
                    message:flags.2?adnl.Message messages:flags.3?(vector adnl.Message)
                    address:flags.6?adnl.addressList seqno:flags.8?long recv_addr_list_version:flags.9?int
                    confirm_seqno:flags.10?long reinit_date:flags.11?int dst_reinit_date:flags.11?int
                    signature:flags.7?bytes rand2:bytes = adnl.PacketContents;

// Magic may be omitted in TL-B
adnl.message.packet packet:bytes = adnl.Message;

adnl.message.createChannel key:int256 date:int = adnl.Message;
adnl.message.confirmChannel key:int256 peer_key:int256 date:int = adnl.Message;

adnl.message.custom data:bytes = adnl.Message;

adnl.message.nop = adnl.Message;
adnl.message.reinit date:int = adnl.Message;

adnl.message.query query_id:int256 query:bytes = adnl.Message;
adnl.message.answer query_id:int256 answer:bytes = adnl.Message;


---functions---
---types---

rldp.messagePart transfer_id:int256 fer_type:fer.Type part:int total_size:long seqno:int data:bytes = rldp.MessagePart;
rldp.confirm transfer_id:int256 part:int seqno:int = rldp.MessagePart;
rldp.complete transfer_id:int256 part:int = rldp.MessagePart;

rldp.message id:int256 data:bytes = rldp.Message;
rldp.query query_id:int256 data:bytes = rldp.Message;
rldp.answer query_id:int256 data:bytes = rldp.Message;


---functions---
---types---

dht.node id:adnl.id.Full addr_list:adnl.addressList version:int signature:bytes = dht.Node;
dht.nodes nodes:(vector dht.node) = dht.Nodes;

dht.key id:int256 name:bytes idx:int = dht.Key;

dht.updateRule.signature = dht.UpdateRule;
dht.updateRule.anybody = dht.UpdateRule;
dht.updateRule.nodes max_nodes:int = dht.UpdateRule;
dht.updateRule.overlayNodes max_nodes:int = dht.UpdateRule;

dht.keyDescription key:dht.key id:adnl.id.Full update_rule:dht.UpdateRule signature:bytes = dht.KeyDescription;

dht.value key:dht.keyDescription value:bytes ttl:int signature:bytes = dht.Value; 

dht.pong random_id:long = dht.Pong;

dht.valueNotFound nodes:dht.nodes = dht.ValueResult;
dht.valueFound value:dht.Value = dht.ValueResult;

dht.stored = dht.Stored;
dht.message node:dht.node = dht.Message;

---functions---

dht.ping random_id:long = dht.Pong;
dht.store value:dht.value = dht.Stored;
dht.findNode key:int256 k:int = dht.Nodes; 
dht.findValue key:int256 k:int = dht.ValueResult; 
dht.getSignedAddressList = adnl.Node;

dht.query node:dht.node = True;

---types---

overlay.node.toSign id:int256 overlay:int256 version:int = overlay.node.ToSign;
overlay.node id:adnl.id.Full overlay:int256 version:int signature:bytes = overlay.Node;
overlay.nodes nodes:(vector overlay.node) = overlay.Nodes;

overlay.message overlay:int256 = overlay.Message;
//overlay.randomPeers peers:(vector adnl.node) = overlay.RandomPeers;
overlay.broadcastList hashes:(vector int256) = overlay.BroadcastList;

overlay.fer.received hash:int256 = overlay.Broadcast;
overlay.fer.completed hash:int256 = overlay.Broadcast;

overlay.broadcast.id src:int256 data_hash:int256 flags:int = overlay.broadcast.Id; 
overlay.broadcastFer.id src:int256 type:int256 data_hash:int256 size:int flags:int = overlay.broadcastFer.Id;
overlay.broadcastFer.partId broadcast_hash:int256 data_hash:int256 seqno:int = overlay.broadcastFer.PartId;

overlay.broadcast.toSign hash:int256 date:int = overlay.broadcast.ToSign;

overlay.certificate issued_by:adnl.id.Full expire_at:int max_size:int signature:bytes = overlay.Certificate;
overlay.emptyCertificate = overlay.Certificate;

overlay.certificateId overlay_id:int256 node:int256 expire_at:int max_size:int = overlay.CertificateId;

overlay.unicast data:bytes = overlay.Broadcast;
overlay.broadcast src:adnl.id.Full certificate:overlay.Certificate flags:int data:bytes date:int signature:bytes = overlay.Broadcast;
overlay.broadcastFer src:adnl.id.Full certificate:overlay.Certificate data_hash:int256 data_size:int flags:int
          data:bytes seqno:int fer:fer.Type date:int signature:bytes = overlay.Broadcast;
overlay.broadcastFerShort src:adnl.id.Full certificate:overlay.Certificate broadcast_hash:int256 part_data_hash:int256 seqno:int signature:bytes = overlay.Broadcast; 
overlay.broadcastNotFound = overlay.Broadcast;

---functions---

overlay.getRandomPeers peers:overlay.nodes = overlay.Nodes;

overlay.query overlay:int256 = True;
overlay.getBroadcast hash:int256 = overlay.Broadcast;
overlay.getBroadcastList list:overlay.broadcastList = overlay.BroadcastList;

---types---

catchain.block.id incarnation:int256 src:int256 height:int data_hash:int256 = catchain.block.Id;
catchain.block.dep src:int height:int data_hash:int256 signature:bytes = catchain.block.Dep;
catchain.block.data prev:catchain.block.dep deps:(vector catchain.block.dep) = catchain.block.Data;
catchain.block incarnation:int256 src:int height:int data:catchain.block.data signature:bytes = catchain.Block;
catchain.blocks blocks:(vector catchain.block) = catchain.Blocks;
catchain.blockUpdate block:catchain.block = catchain.Update;

catchain.block.data.badBlock block:catchain.block = catchain.block.inner.Data;
catchain.block.data.fork left:catchain.block.Dep right:catchain.block.Dep = catchain.block.inner.Data;
catchain.block.data.nop = catchain.block.inner.Data;
catchain.block.data.vector msgs:(vector bytes) = catchain.block.inner.Data;
//catchain.block.data.custom = catchain.block.inner.Data;

catchain.firstblock unique_hash:int256 nodes:(vector int256) = catchain.FirstBlock;

catchain.difference sent_upto:(vector int) = catchain.Difference;
catchain.differenceFork left:catchain.block.dep right:catchain.block.dep = catchain.Difference;

catchain.blockNotFound = catchain.BlockResult;
catchain.blockResult block:catchain.block = catchain.BlockResult;

catchain.sent cnt:int = catchain.Sent;

---functions---

catchain.getBlock block:int256 = catchain.BlockResult;
catchain.getBlocks blocks:(vector int256) = catchain.Sent;
catchain.getDifference rt:(vector int) = catchain.Difference;
catchain.getBlockHistory block:int256 height:long stop_if:(vector int256) = catchain.Sent;
//catchain.getForkDifference src:int fork:catchain.fork = catchain.ForkDifference;

---types---

validatorSession.id slice:int256 start_time:int end_time:int participants:(vector int256) = validatorSession.Id;
validatorSession.round.id session:int256 height:long prev_block:int256 seqno:int = validatorSession.round.Id;

validatorSession.candidate.id round:int256 block_hash:int256 = validatorSession.tempBlock.Id;

validatorSession.message.startSession = validatorSession.Message;
validatorSession.message.finishSession = validatorSession.Message;

validatorSession.message.submittedBlock round:int root_hash:int256 file_hash:int256 
               collated_data_file_hash:int256 = validatorSession.round.Message;
validatorSession.message.approvedBlock round:int candidate:int256 = validatorSession.round.Message;
validatorSession.message.commit round:int candidate:int256 signature:bytes = validatorSession.round.Message;

validatorSession.message.vote round:int attempt:int candidate:int256 = validatorSession.round.Message;
validatorSession.message.precommit round:int attempt:int candidate:int256 = validatorSession.round.Message;
validatorSession.message.empty round:int attempt:int = validatorSession.round.Message;

validatorSession.pong hash:long = validatorSession.Pong;

validatorSession.candidateId src:int256 root_hash:int256 file_hash:int256 collated_data_file_hash:int256 = validatorSession.CandidateId;

validatorSession.blockUpdate ts:long actions:(vector validatorSession.round.Message) state:int = validatorSession.BlockUpdate;
validatorSession.candidate src:int256 round:int root_hash:int256 data:bytes collated_data:bytes = validatorSession.Candidate;

---functions---

validatorSession.ping hash:long = validatorSession.Pong;
validatorSession.downloadCandidate round:int id:validatorSession.candidateId = validatorSession.Candidate; 

---types---

hashable.bool value:Bool = Hashable;
hashable.int32 value:int = Hashable;
hashable.int64 value:long = Hashable;
hashable.int256 value:int256 = Hashable;
hashable.bytes value:bytes = Hashable;
hashable.pair left:int right:int = Hashable;
hashable.vector value:(vector int) = Hashable;
hashable.validatorSessionOldRound seqno:int block:int signatures:int = Hashable;
hashable.validatorSessionRoundAttempt seqno:int votes:int precommitted:int = Hashable;
hashable.validatorSessionRound locked_round:int locked_block:int seqno:int precommitted:Bool
          approved_blocks:int signatures:int attempts:int = Hashable;
hashable.blockSignature signature:int = Hashable;
hashable.sentBlock src:int root_hash:int file_hash:int collated_data_file_hash:int = Hashable; 
hashable.sentBlockEmpty = Hashable;
hashable.vote block:int node:int = Hashable;
hashable.blockCandidate block:int approved:int = Hashable;
hashable.blockCandidateAttempt block:int votes:int = Hashable;

hashable.cntVector data:int = Hashable;
hashable.cntSortedVector data:int = Hashable;

hashable.validatorSession ts:int old_rounds:int cur_round:int = Hashable;

---functions---
---types---


tonNode.sessionId workchain:int shard:long utime_from:int utime_to:int = tonNode.SessionId; 


tonNode.blockSignature who:int256 signature:bytes = tonNode.BlockSignature;

tonNode.blockIdExt workchain:int shard:long seqno:int root_hash:int256 file_hash:int256 = tonNode.BlockIdExt;
tonNode.zeroStateIdExt workchain:int root_hash:int256 file_hash:int256 = tonNode.ZeroStateIdExt;

tonNode.blockDescriptionEmpty = tonNode.BlockDescription;
tonNode.blockDescription id:tonNode.blockIdExt = tonNode.BlockDescription;
tonNode.preparedProofEmpty = tonNode.PreparedProof;
tonNode.preparedProof masterchain_block:tonNode.blockIdExt = tonNode.PreparedProof;
tonNode.preparedProofLink = tonNode.PreparedProof;
tonNode.preparedState = tonNode.PreparedState;
tonNode.notFoundState = tonNode.PreparedState;
tonNode.prepared = tonNode.Prepared;
tonNode.notFound = tonNode.Prepared;
tonNode.data data:bytes = tonNode.Data;

tonNode.ihrMessage data:bytes = tonNode.IhrMessage;
tonNode.externalMessage data:bytes = tonNode.ExternalMessage;

tonNode.newShardBlock workchain:int shard:long data:bytes = tonNode.NewShardBlock;

tonNode.blockBroadcast id:tonNode.blockIdExt catchain_seqno:int validator_set_hash:int 
              signatures:(vector tonNode.blockSignature) masterchain_block_id:tonNode.blockIdExt
              proof:bytes data:bytes = tonNode.Broadcast;
tonNode.ihrMessageBroadcast message:tonNode.ihrMessage = tonNode.Broadcast;
tonNode.externalMessageBroadcast message:tonNode.externalMessage = tonNode.Broadcast;
tonNode.newShardBlockBroadcast block:tonNode.newShardBlock = tonNode.Broadcast;

tonNode.shardPublicOverlayId workchain:int shard:long = tonNode.ShardPublicOverlayId;

ton.blockId root_cell_hash:int256 file_hash:int256 = ton.BlockId;

---functions---

tonNode.getNextBlockDescription prev_block:tonNode.blockIdExt = tonNode.BlockDescription;
tonNode.prepareBlockProof block:tonNode.blockIdExt allow_partial:Bool = tonNode.PreparedProof;
tonNode.prepareBlock block:tonNode.blockIdExt = tonNode.Prepared;
tonNode.prepareState block:tonNode.blockIdExt = tonNode.PreparedState;
tonNode.downloadBlock block:tonNode.blockIdExt = tonNode.Data;
tonNode.downloadState block:tonNode.blockIdExt = tonNode.Data;
tonNode.downloadBlockProof block:tonNode.blockIdExt = tonNode.Data;
tonNode.downloadBlockProofLink block:tonNode.blockIdExt = tonNode.Data;

---types---

liteServer.error code:int message:string = liteServer.Error; 

---functions---
---types---

test.validatorSession.block root_hash:int256 height:long data:bytes = test.validatorSession.Block;

test0.blockSignatures signatures:(vector tonNode.blockSignature) = test0.BlockSignatures;

test0.proofLink id:tonNode.blockIdExt prev:(vector tonNode.blockIdExt) state:int256 split:Bool = test.ProofLink; 
test0.proof link:test0.proofLink catchain_seqno:int validator_set_hash:int signatures:test0.blockSignatures = test.Proof;

test0.masterchain.shardInfo last_block:tonNode.blockIdExt before_merge:Bool before_split:Bool after_merge:Bool after_split:Bool 
          = test0.masterchain.ShardInfo;

test0.masterchainBlockExtra.empty = test0.MasterchainBlockExtra;
test0.masterchainBlockExtra.extra randseed:int rotate:Bool shards:(vector test0.masterchain.shardInfo) = test0.MasterchainBlockExtra;

test0.masterchainStateExtra.empty = test0.MasterchainStateExtra;
test0.masterchainStateExtra.extra validator_ts:int validator_randseed:int next_randseed:int next_rotate_at:int prev_blocks:(vector tonNode.blockIdExt) shards:(vector test0.masterchain.shardInfo) pool:(vector adnl.id.Full) = test0.MasterchainStateExtra;

test0.shardchain.block workchain:int shard:long seqno:int prev:(vector tonNode.blockIdExt) split:Bool ts:int state:int256 
            catchain_seqno:int validator_set_hash:int pad:bytes extra:test0.MasterchainBlockExtra = test.shardchain.Block;
test0.shardchain.state workchain:int shard:long seqno:int ts:int split:Bool extra:test0.MasterchainStateExtra = test.shardchain.State; 

test0.topShardBlockDescription block_id:tonNode.blockIdExt after_split:Bool after_merge:Bool before_split:Bool 
  catchain_seqno:int validator_set_hash:int signatures:bytes = test0.TopShardBlockDescription;

test0.validatorSessionId workchain:int shard:long shard_from:long ts:int = test0.ValidatorSessionId;

test0.validatorSetItem id:int256 weight:long = test0.ValidatorSetItem;
test0.validatorSet ts:int validators:(vector test0.validatorSetItem) = test0.ValidatorSet; 

test0.extMessage workchain:int shard:long data:bytes = test0.ExtMessage;

---functions---

---types---

// bit 0 - started
// bit 1 - ready to switch
// bit 2 - switched from
// bit 3 - archived
// bit 4 - disabled

db.root.dbDescription version:int first_masterchain_block_id:tonNode.blockIdExt flags:int = db.root.DbDescription;

db.root.key.cellDb version:int = db.root.Key; 
db.root.key.blockDb version:int = db.root.Key; 

db.root.config celldb_version:int blockdb_version:int = db.root.Config;
db.root.key.config = db.root.Key;

db.celldb.value next:tonNode.blockIdExt hash:int256 = db.celldb.Value;
db.celldb.key.value id:tonNode.blockIdExt = db.celldb.key.Value;

db.block.info id:tonNode.blockIdExt flags:# prev_left:flags.1?tonNode.blockIdExt
                                            prev_right:flags.2?tonNode.blockIdExt
                                            next_left:flags.3?tonNode.blockIdExt
                                            next_right:flags.4?tonNode.blockIdExt
                                            lt:flags.13?long 
                                            state:flags.17?int256 = db.block.Info;
db.block.archivedInfo id:tonNode.blockIdExt flags:# next:flags.0?tonNode.blockIdExt = db.block.Info;

db.blockdb.value next:tonNode.blockIdExt data:bytes = db.blockdb.Value;
db.blockdb.key.value id:tonNode.blockIdExt = db.blockdb.key.Value;

db.filedb.value next:db.filedb.Key hash:int256 = db.filedb.Value;

db.candidate id:tonNode.blockIdExt data:bytes collated_data:bytes = db.Candidate;
db.candidate.id id:tonNode.blockIdExt collated_data_file_hash:int256 = db.candidate.Id; 

db.filedb.key.empty = db.filedb.Key;
db.filedb.key.blockFile block_id:tonNode.blockIdExt = db.filedb.Key; 
db.filedb.key.stateFile block_id:tonNode.blockIdExt = db.filedb.Key; 
db.filedb.key.shardStateFile block_id:tonNode.blockIdExt masterchain_block_id:tonNode.blockIdExt = db.filedb.Key; 
db.filedb.key.proof block_id:tonNode.blockIdExt = db.filedb.Key;
db.filedb.key.proofLink block_id:tonNode.blockIdExt = db.filedb.Key;
db.filedb.key.signatures block_id:tonNode.blockIdExt = db.filedb.Key;
db.filedb.key.candidate id:db.candidate.id = db.filedb.Key;

db.state.destroyedSessions sessions:(vector int256) = db.state.DestroyedSessions;
db.state.initBlockId block:tonNode.blockIdExt = db.state.InitBlockId;
db.state.shardClient block:tonNode.blockIdExt = db.state.ShardClient;

db.state.key.destroyedSessions = db.state.Key;
db.state.key.initBlockId = db.state.Key;
db.state.key.shardClient workchain:int shard:long = db.state.Key;

---functions---

---types---

id.config.local id:adnl.id.Pk addr_list:adnl.addressList = id.config.Local;
dht.config.local id:adnl.id.short = dht.config.Local;
dht.config.random.local cnt:int addr_list:adnl.addressList = dht.config.Local;
overlay.config.local name:bytes id:adnl.id.short = overlay.config.Local;
overlay.config.random.local cnt:int name:bytes addr_list:adnl.addressList = overlay.config.Local;
catchain.config.local tag:int256 id:adnl.id.short = catchain.config.Local;
liteserver.config.local id:adnl.id.Pk port:int = liteserver.config.Local;
dummyworkchain0.config.local id:adnl.id.short = dummyworkchain0.config.Local;
validator.config.local id:adnl.id.short = validator.config.Local;
config.local udp_ports:(vector int) tcp_ports:(vector int) local_ids:(vector id.config.local) dht:(vector dht.config.Local) public_overlays:(vector overlay.config.Local) catchains:(vector catchain.config.local) dummy0:(vector dummyworkchain0.config.local) validators:(vector validator.config.local) liteservers:(vector liteserver.config.local) = config.Local;

dht.config.global static_nodes:dht.nodes k:int a:int = dht.config.Global;
adnl.config.global static_nodes:adnl.nodes = adnl.config.Global;
catchain.config.global tag:int256 nodes:(vector adnl.id.Full) = catchain.config.Global;
liteclient.config.global id:adnl.id.Full ip:int port:int = liteserver.config.Global;
dummyworkchain0.config.global zero_state_hash:int256 = dummyworkchain0.config.Global;
validator.config.global zero_state_root_hash:int256 zero_state_file_hash:int256 = validator.config.Global;
config.global adnl:adnl.config.global dht:dht.config.global catchains:(vector catchain.config.global) dummy0:(vector dummyworkchain0.config.global)
        validators:(vector validator.config.global) liteclients:(vector liteclient.config.global) = config.Global;

---functions---

---types---
liteServer.accountId workchain:int id:int256 = liteServer.AccountId;

liteServer.masterchainInfo last:tonNode.blockIdExt state_root_hash:int256 init:tonNode.zeroStateIdExt = liteServer.MasterchainInfo;
liteServer.currentTime now:int = liteServer.CurrentTime;
liteServer.blockData id:tonNode.blockIdExt data:bytes = liteServer.BlockData;
liteServer.blockState id:tonNode.blockIdExt root_hash:int256 file_hash:int256 data:bytes = liteServer.BlockState;
liteServer.blockHeader id:tonNode.blockIdExt mode:# header_proof:bytes = liteServer.BlockHeader;
liteServer.sendMsgStatus status:int = liteServer.SendMsgStatus;
liteServer.accountState id:tonNode.blockIdExt shardblk:tonNode.blockIdExt shard_proof:bytes proof:bytes state:bytes = liteServer.AccountState;
liteServer.shardInfo id:tonNode.blockIdExt shardblk:tonNode.blockIdExt shard_proof:bytes shard_descr:bytes = liteServer.ShardInfo;
liteServer.allShardsInfo id:tonNode.blockIdExt proof:bytes data:bytes = liteServer.AllShardsInfo;

liteServer.debug.verbosity value:int = liteServer.debug.Verbosity;

---functions---

liteServer.getMasterchainInfo = liteServer.MasterchainInfo;
liteServer.getTime = liteServer.CurrentTime;
liteServer.getBlock id:tonNode.blockIdExt = liteServer.BlockData;
liteServer.getState id:tonNode.blockIdExt = liteServer.BlockState;
liteServer.getBlockHeader id:tonNode.blockIdExt mode:# = liteServer.BlockHeader;
liteServer.sendMessage body:bytes = liteServer.SendMsgStatus;
liteServer.getAccountState id:tonNode.blockIdExt account:liteServer.accountId = liteServer.AccountState;
liteServer.getShardInfo id:tonNode.blockIdExt workchain:int shard:long exact:Bool = liteServer.ShardInfo;
liteServer.getAllShardsInfo id:tonNode.blockIdExt = liteServer.AllShardsInfo;

liteServer.debug.setVerbosity verbosity:liteServer.debug.verbosity = liteServer.debug.Verbosity;

liteServer.query data:bytes = Object;
