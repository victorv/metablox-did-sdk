//
//  main.c
//  did_demo
//
//  Created by liudeng on 2022/2/23.
//

#include <stdio.h>
#include "did_wallet/did_wallet.h"
#include "did/did.h"
#include "string.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    char buffer1[2048] = {0};
    char buffer2[2048] = {0};
    size_t buff_len = 2048;
    did_handle did = did_create("secp256k1", NULL);

    wallet_handle wallet= wallet_handle_create("test-did", "/home/meiqiu/doc/did_sdk-main2/build/test");

    wallet_store_did(wallet, did, "test-did", "12345678");

    did_handle did2 = wallet_load_did(wallet, "test-did", "12345678");

    did_serialize(did, buffer1, buff_len);

    did_serialize(did2, buffer2, buff_len);

    char sig[64] = {0};
    int did_sign_result=did_sign(did, "Hello, World!", strlen("Hello, World!"), sig, 64);

    did_meta_t* did2_meta = did_to_did_meta(did2);

    int verify = did_verify(did2_meta->did_keys, "Hello, World!", strlen("Hello, World!"), sig, 64);

    //2022.4.25
    printf("\n did_priv key:%s",did_export_prikey(did));
    did_sign_res* result=did_get_vrs(sig,verify);

    printf("\nHello, World! Verif yesult %d\n", verify);
    return 0;
}
