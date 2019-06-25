# TON Research

This is open development community and **enthusiasts research place**. We will post our news and updates this project there.

---
## Table of contents:

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->

- [About source and github repositories](#about-source-and-github-repositories)
- [TON whitepapers:](#ton-whitepapers)
- [TON source code](#ton-source-code)
  - [Source code check](#source-code-check)
- [What we already did:](#what-we-already-did)
- [Future steps:](#future-steps)
- [Installation & Setup](#installation--setup)
- [Tutorial](#tutorial)
- [Contributing](#contributing)
- [Contact us](#contact-us)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## About source and github repositories
- http://test.ton.org/downloads.html - is the "official"* ton client tarball
- https://github.com/copperbits/TON - community version with added features but sometimes outdated code and releases
- https://github.com/poma/ton-lite-client - unchanged up to date version of tarball but on github. Also fresh binaries and docker container

\*There is no official statement that ton.org is related to TON network. But this is only one real source of information and code at this moment.

## TON whitepapers:

- [List of available files](https://test.ton.org/download.html) – List of available files
  - [Telegram Open Network Whitepaper](https://test.ton.org/ton.pdf) – a general description
  - [Telegram Open Network Virtual Machine](https://test.ton.org/tvm.pdf) - TON Virtual Machine description
  - [Telegram Open Network Blockchain](https://test.ton.org/tblkch.pdf) - TON Blockchain description (possibly a bit out of date)
  - [Fift: A Brief Introduction](https://test.ton.org/fiftbase.pdf) - A brief introduction to Fift programming language
  - [README](https://test.ton.org/README.txt) -
  General information, compilation and installation instructions
  - [HOWTO](https://test.ton.org/HOWTO.txt) - Step-by-step description of creation of a new smart contract with the aid of the Lite Client

## TON source code

Code was downloaded from https://test.ton.org/download.html

Last codebase update was performed on June 5, 2019.`sha256sum('ton-test-liteclient-full.tar.xz')`=`edd57971cba5cff9b219a1c99401a7315176ac9ab30afc9df0b1ed39e1dbc009`.

### Source code check

Run a command `./ton-test-liteclient-full/check_codebase.sh` while updating a codebase to be sure it's up-to-date

## What we already did:
- 📖 Documentations:
  - 🐧 Added build instructions for [ubuntu 16.04](https://github.com/copperbits/TON/blob/master/docs/ubuntu16.04.sh)
  - 📩 Explain in [video on YouTube](https://www.youtube.com/watch?v=J7K2nq5lf7I) and [text on GitHub](/docs/Mac_tutorial.md), how to start Lite Client on macOS and send transactions to TON network
  - 🇨🇳 Wrote an [article](https://mp.weixin.qq.com/s/WLlD088acBDfjUM4bCEd0A) about the TON in Chinese and began to translate [TON whitepaper into Сhinese](https://drive.google.com/file/d/1acH4j7zY_XhsOUGsup4byssMXlp5000O/view) (by toozWu)

- Helpful sources:
  - 🏗 Build lite client node: [Latest release](https://github.com/copperbits/TON/releases/latest)
  - 🐳 Packaged lite client into [Docker](https://github.com/copperbits/TON#docker)  container
  - 👓 Launched a [beta explorer](https://explorer.test.ton.cryptoprocessing.io/) for test network
  - 💸 Made a UI friendly [faucet for TON](https://faucet.copperbits.io/)
  - 🔁 Created [mirror with updates it builds binaries and docker container on any changes in source code](https://github.com/poma/ton-lite-client) updates any 5 minutes (former TON-mirror)
  - 📣 Created Telegram bot post message about updates [here](https://t.me/ton_research) and [here](https://t.me/TrackingTONupdates) - with any new commits into original repo
  - ✨ Created [Webserver](/docs/WEB_SERVER.md) which realizes a web client for TON
  - 🌐 [Public node](https://explorer.test.ton.cryptoprocessing.io/api) of [web client for TON](/docs/WEB_SERVER.md)

- 🎓 Now we are writing video tutorials, writing manuals / FAQ / HOWTO how to use TON.

👉 _pull request and suggestions are **[very welcome](https://github.com/copperbits/TON/issues/new)**!_

![CLient lunch](img/run_client.png)

## Future steps:

**Creating FAQ & Video tutorial (WIP):**
_✨feel free to propose your topics_
- Step-by-step guide: **How to build a TON client**
- How to get test Grams
- Development:
  - Write first hello-world smart contract
  - How to deploy a smart contract
  - How to send transactions

**Also, you will find there:**
- Future releases of binaries
- A FAQ with most popular questions (WIP)

## Installation & Setup

There are two options. By running Docker or precompiled binary for macOS below:

**Docker**

The easiest way to run the node in a docker container:

```
docker run -d copperbits/ton
```

You might want to run in interactive mode and mount current dir into the container to be able to compile fif files:

```
docker run -ti -v "$(pwd):/data" --name ton copperbits/ton
```

Compile a fif file (if your container is running and current dir is mounted):

```
docker exec ton fift test.fif
```

**Releases (macOS)**

[Lite Client Latest release](https://github.com/copperbits/TON/releases/latest)

- Download [latest release](https://github.com/copperbits/TON/releases/)
- Go to command line, where binary placed
- Run:
```bash
./test-lite-client -C ton-lite-client-test1.config.json
```
- run `help` to get started

More detailed instruction you can find [here](/docs/Mac_tutorial.md).

## Tutorial

All educational thing we moved it to [docs](/docs) folder.
You will find here [original readme](/docs/README.md), with additions of community-based tools and educational materials.


## Contributing

All this information shipped by [copperbits team](tg://resolve?domain=ton_research) and [contributors](https://github.com/copperbits/TON/graphs/contributors) :clap:


- **Questions?** Feel free to [open an issue](https://github.com/copperbits/TON/issues/new). Or ask us on [Telegam public group](tg://resolve?domain=ton_research)
- If you find **bugs, got suggestions**, or even feature requests: [open an issue](https://github.com/copperbits/TON/issues/new) :octocat:
- Star [GitHub repo](https://github.com/copperbits/TON/) to **support this project** :+1:
- **Want to share something?** Feel free to add related stuff to [awesome-ton](https://github.com/copperbits/awesome-ton) repo
- The **license** in [GNU Lesser General Public License v2.1
](https://github.com/copperbits/TON/blob/master/LICENSE) :unlock:
- Your **contributions are appreciated**. You can follow [CONTRIBUTING](https://github.com/copperbits/TON/blob/master/CONTRIBUTING.md) guide to get everything started.

## Contact us

Here is [Telegam public group](tg://resolve?domain=ton_research) -  feel free to **ask any questions and proposals** there :+1:
