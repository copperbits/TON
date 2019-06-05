## Create a new wallet and get test Grams
1. Clone repo 'git clone https://github.com/copperbits/TON.git'
2. Create "builds" directory and download there files "test-lite-client", "fift", "ton-lite-client-test1.config.json" from  (click "Keep" if your browser blocks the download)
3. Change permissions of downloaded files 'chmod +x fift', 'chmod +x test-lite-client'.
4. Create a file "new-wallet.fif" in "builds" and copy the code from section “Compiling a new smart contract” of the instruction https://test.ton.org/HOWTO.txt into the file.
4.1  Set the FIFTPATH environment variable to “/crypto/fift” (the directory containing Fift.fif and Asm.fif library files).
4.2* If you don’t have gflags you should install it 'brew install gflags' (maybe you will have to change the ownership of some directories to yourself).
5. Compile file “new-wallet.fif” with fift compiler: './fift new-wallet.fif' and copy a new wallet address from the output - you will need it soon. Result will be saved to the file "new-wallet-query.boc", and the private key of the new wallet will be saved into the file “new-wallet.pk” (be careful not to run this code twice in the same directory, otherwise this private key file will be overwritten).
6. You need some Grams to deploy your smartcontract. At first create file "testgiver.fif" in the directory “builds” and copy there "Compiling a new smart contract" from https://test.ton.org/HOWTO.txt
7. Replace address "60c04141c6a7b96d68615e7a91d265ad0f3a9a922e9ae9c901d4fa83f5d3c0d0" with your wallet address in testgiver.fif. You may also enter any other amount up to approximately 20 Grams instead of "6.666 Gram" (but don't remove the dot).
8. Run your lite testnet node './test-lite-client -C ton-lite-client-test1.config.json'. Sometimes testnet is down. You can check testnet status in the telegram channel https://t.me/testnetstatus.
If it is up, get the last block  with a command 'last' and get a nonce from account info 'getaccount -1:8156775b79325e5d62e742d9b96c30b6515a5cd2f1f64c5da4b193c03f070e0d' ("8156775b79325e5d62e742d9b96c30b6515a5cd2f1f64c5da4b193c03f070e0d" is the test giver address). Last value like "0x00000236" is the last nonce.  Copy this number and paste it instead of zero into the string "0 constant seqno"  in "testgiver.fif", to produce a string like  "0x00000236 constant seqno".
9. Compile your file './fift testgiver.fif'. Output will be saved to "wallet-query.boc"
10. Go back to your node interface and send the file with the result of the compilation: 'sendfile wallet-query.boc'.
11. Download the last block (command 'last') and check your account balance 'getaccount -1:{your address}'.
12. Deploy a new wallet by sending the result of the compilation "new-wallet.fif"  with a command 'sendfile new-wallet-query.boc'
13. Download the last block (command 'last') and check that there is new data in your account: 'getaccount -1:{your address}'.

## Send transaction
1. Copy code from “Using the simple wallet smart contract” of the instruction https://test.ton.org/HOWTO.txt into a new file “SendTx.sh”
2. Replace zero in line “0 constant seqno” with the actual nonce of your address
3. Replace “1000000000” in line “1000000000 constant Gram” with amount of Grams you want to send and change the destination address.
4. Replace output file name with “-query-sendtx.boc” on the last line.
5. Correct path to fift in the first line.
6. Change permissions: ‘chmod +x SendTx.sh’
7. Send transaction: ‘./SendTx.sh new-wallet'
8. Send result file: ‘sendfile new-wallet-query-sendtx.boc’
9. Download the last block: ‘last’, and check that your account balance has been changed: ‘getaccount -1:{your address}’
