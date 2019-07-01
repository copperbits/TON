double ? = Double;
string ? = String;

int32 = Int32;
int53 = Int53;
int64 = Int64;
bytes = Bytes;

boolFalse = Bool;
boolTrue = Bool;

vector {t:Type} # [ t ] = Vector t;

error code:int32 message:string = Error;
ok = Ok;

privateKey key:bytes = PrivateKey;
publicKey key:bytes = PublicKey;

accountAddress account_address:string = AccountAddress;

raw.initialAccountState code:bytes data:bytes = raw.InitialAccountState;
raw.accountState balance:int64 code:bytes data:bytes = raw.AccountState;

testWallet.initialAccountState public_key:PublicKey = testWallet.InitialAccountState;
testWallet.accountState balance:int64 seqno:int32 = testWallet.AccountState;

testGiver.accountState balance:int64 seqno:int32 = testGiver.AccountState;

uninited.accountState balance:int64 = uninited.AccountState;

generic.initialAccountStateRaw initital_account_state:raw.initialAccountState = generic.InitialAccountState;
generic.initialAccountStateTestWallet initital_account_state:testWallet.initialAccountState = generic.InitialAccountState;

generic.accountStateRaw account_state:raw.accountState = generic.AccountState;
generic.accountStateTestWallet account_state:testWallet.accountState = generic.AccountState;
generic.accountStateTestGiver account_state:testGiver.accountState = generic.AccountState;
generic.accountStateUninited account_state:uninited.accountState = generic.AccountState;

---functions---

options.setConfig config:string = Ok;

createKey = PrivateKey;
getPublicKey private_key:privateKey = PublicKey;

//raw.init initial_account_state:raw.initialAccountState = Ok;
raw.getAccountAddress initital_account_state:raw.initialAccountState = AccountAddress;
raw.getAccountState account_address:accountAddress = raw.AccountState;
raw.sendMessage destination:accountAddress initial_account_state:bytes data:bytes = Ok;

testWallet.init private_key:PrivateKey = Ok;
testWallet.getAccountAddress initital_account_state:testWallet.initialAccountState = AccountAddress;
testWallet.getAccountState account_address:accountAddress = testWallet.AccountState;
testWallet.sendGrams private_key:PrivateKey destination:accountAddress seqno:int32 amount:int64 = Ok;

testGiver.getAccountState = testGiver.AccountState;
testGiver.getAccountAddress = AccountAddress;
testGiver.sendGrams destination:accountAddress seqno:int32 amount:int64 = Ok;

//generic.getAccountAddress initital_account_state:generic.InitialAccountState = AccountAddress;
generic.getAccountState account_address:accountAddress = generic.AccountState;
generic.sendGrams private_key:PrivateKey source:accountAddress destination:accountAddress amount:int64 = Ok;

runTests dir:string = Ok;

---types---
key public_key:bytes secret:bytes = Key;
inputKey key:key local_password:bytes = InputKey;
exportedKey word_list:vector<string> = ExportedKey;
exportedPemKey pem:string= ExportedPemKey;
--- functions ---
createNewKey local_password:bytes mnemonic_password:bytes = Key;
deleteKey public_key:bytes = Ok;
exportKey input_key:inputKey = ExportedKey;
exportPemKey input_key:inputKey key_password:bytes = ExportedPemKey;
importKey local_password:bytes mnemonic_password:bytes exported_key:exportedKey = Key;
importPemKey local_password:bytes key_password:bytes exported_key:exportedPemKey = Key;
changeLocalPassword input_key:inputKey new_local_password:bytes = Key;
