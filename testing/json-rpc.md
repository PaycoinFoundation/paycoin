Test JSON-RPC
=============

Test of the JSON-RPC features using [curl](http://curl.haxx.se/) to make the HTTP requests.


Simple JSON-RPC
---------------

We send one request and we get one response.

curl --user user:password --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getinfo", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:9904/

    {
      "result" : {
        "version" : "v0.4.0ppc-58-g0cf220b-dirty-beta",
        "protocolversion" : 60004,
        "walletversion" : 60000,
        "balance" : 44857.07000000,
        "newmint" : 0.00000000,
        "stake" : 0.00000000,
        "blocks" : 84085,
        "moneysupply" : 93170862.35542700,
        "connections" : 8,
        "proxy" : "",
        "ip" : "0.1.2.3",
        "difficulty" : 0.06249911,
        "testnet" : true,
        "keypoololdest" : 1397665693,
        "keypoolsize" : 103,
        "paytxfee" : 0.01000000,
        "errors" : ""
      },
      "error" : null,
      "id" : "curltest"
    }


Batch JSON-RPC
--------------

We send several requests in an array and we get an array of responses.

curl --user user:password --data-binary '[{"jsonrpc": "1.0", "id":"curltest1", "method": "getinfo", "params": [] }, {"jsonrpc": "1.0", "id":"curltest2", "method": "getbalance", "params": ["addr1"] }, {"jsonrpc": "1.0", "id":"curltest3", "method": "getbalance", "params": ["addr2"] }]' -H 'content-type: text/plain;' http://127.0.0.1:9904/

    [
      {
        "result" : {
          "version" : "v0.4.0ppc-58-g0cf220b-dirty-beta",
          "protocolversion" : 60004,
          "walletversion" : 60000,
          "balance" : 44857.07000000,
          "newmint" : 0.00000000,
          "stake" : 0.00000000,
          "blocks" : 84086,
          "moneysupply" : 93170862.53542700,
          "connections" : 8,
          "proxy" : "",
          "ip" : "0.1.2.3",
          "difficulty" : 0.06249911,
          "testnet" : true,
          "keypoololdest" : 1397665693,
          "keypoolsize" : 103,
          "paytxfee" : 0.01000000,
          "errors" : ""
        },
        "error" : null,
        "id" : "curltest1"
      },
      {
        "result" : 31049.58000000,
        "error" : null,
        "id" : "curltest2"
      },
      {
        "result" : 10747.50000000,
        "error" : null,
        "id" : "curltest3"
      }
    ]
