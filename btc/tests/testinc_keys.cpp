////////////////////////////////////////////////////////////////////////
//FAKE関数

//FAKE_VALUE_FUNC(int, external_function, int);

////////////////////////////////////////////////////////////////////////

class keys: public testing::Test {
protected:
    virtual void SetUp() {
        //RESET_FAKE(external_function)
        utl_dbg_malloc_cnt_reset();
        btc_init(BTC_TESTNET, false);
    }

    virtual void TearDown() {
        ASSERT_EQ(0, utl_dbg_malloc_cnt());
        btc_term();
    }

public:
    static void DumpBin(const uint8_t *pData, uint16_t Len)
    {
        for (uint16_t lp = 0; lp < Len; lp++) {
            printf("%02x", pData[lp]);
        }
        printf("\n");
    }
};

////////////////////////////////////////////////////////////////////////

TEST_F(keys, keys_is_valid_priv1)
{
    const uint8_t PRIV[] = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
    };
    bool ret = btc_keys_chkpriv(PRIV);
    ASSERT_FALSE(ret);
}

TEST_F(keys, keys_is_valid_priv2)
{
    const uint8_t PRIV[] = {
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,1,
    };
    bool ret = btc_keys_chkpriv(PRIV);
    ASSERT_TRUE(ret);
}

TEST_F(keys, keys_is_valid_priv3)
{
    const uint8_t PRIV[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B,
        0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x40,
    };
    bool ret = btc_keys_chkpriv(PRIV);
    ASSERT_TRUE(ret);
}

TEST_F(keys, keys_is_valid_priv4)
{
    const uint8_t PRIV[] = {
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
        0xBA, 0xAE, 0xDC, 0xE6, 0xAF, 0x48, 0xA0, 0x3B,
        0xBF, 0xD2, 0x5E, 0x8C, 0xD0, 0x36, 0x41, 0x41,
    };
    bool ret = btc_keys_chkpriv(PRIV);
    ASSERT_FALSE(ret);
}


TEST_F(keys, keys_1)
{
    const char WIF[] = "cUU6xf1CZww9yU67yNvcbgK77un6FA2stzDXbH3XNqtcnK71sKuA";
    const uint8_t PRIV[] = {
        0xcd, 0x77, 0xac, 0xa0, 0x01, 0xfe, 0x88, 0xe8,
        0xf2, 0xdc, 0xdc, 0xc7, 0xfc, 0xd8, 0x6c, 0x34,
        0xd2, 0xaf, 0x54, 0x66, 0x82, 0xcf, 0xed, 0xe6,
        0x5f, 0x9e, 0xd8, 0x48, 0xa8, 0x1d, 0xfa, 0xc6,
    };
    const uint8_t PUB[] = {
        0x03, 0xbe, 0xce, 0xc4, 0x1f, 0x68, 0xd7, 0x7f,
        0xde, 0x9e, 0x97, 0x2c, 0x79, 0xaa, 0x0e, 0x6e,
        0x4e, 0x81, 0x8b, 0xd3, 0x04, 0x62, 0x76, 0x96,
        0x9e, 0x79, 0x37, 0x4e, 0xc0, 0x56, 0x1b, 0xa4,
        0x59,
    };
    const uint8_t UNCOMPPUB[] = {
        0xbe, 0xce, 0xc4, 0x1f, 0x68, 0xd7, 0x7f, 0xde,
        0x9e, 0x97, 0x2c, 0x79, 0xaa, 0x0e, 0x6e, 0x4e,
        0x81, 0x8b, 0xd3, 0x04, 0x62, 0x76, 0x96, 0x9e,
        0x79, 0x37, 0x4e, 0xc0, 0x56, 0x1b, 0xa4, 0x59,
        0x13, 0xb9, 0x8e, 0x22, 0xe8, 0x82, 0x13, 0x37,
        0xf2, 0x67, 0xbb, 0x59, 0xfc, 0xd1, 0x90, 0xb8,
        0x43, 0xe0, 0x09, 0x93, 0x69, 0x83, 0xb7, 0xf6,
        0x2a, 0x82, 0x47, 0x66, 0x21, 0xdb, 0x7e, 0xcd,
    };
    const uint8_t PKH[] = {
        0xad, 0x3d, 0xc2, 0xf5, 0x22, 0x96, 0xf9, 0x3c,
        0x78, 0x98, 0xeb, 0x63, 0x8b, 0x0d, 0x74, 0xf2,
        0x7d, 0x79, 0xef, 0xc3,
    };
    const char ADDR[] = "mwJyBWTEUYMdJ12JWwK3eXff48pxQU6685";
    const char WADDR[] = "2NFqpHBHpWfbL2b4wuBekAsCWv12UerQXiR";

    bool ret;
    uint8_t priv[BTC_SZ_PRIVKEY];
    uint8_t pub[BTC_SZ_PUBKEY];
    uint8_t uncomppub[BTC_SZ_PUBKEY_UNCOMP - 1];
    uint8_t pkh2[BTC_SZ_PUBKEYHASH];
    char addr[BTC_SZ_ADDR_STR_MAX + 1];
    char waddr[BTC_SZ_ADDR_STR_MAX + 1];
    btc_chain_t chain;

    ret = btc_keys_wif2priv(priv, &chain, WIF);
    ASSERT_TRUE(ret);
    ASSERT_EQ(0, memcmp(PRIV, priv, sizeof(PRIV)));
    ASSERT_EQ(BTC_TESTNET, chain);

    char wif[BTC_SZ_WIF_MAX + 1];
    ret = btc_keys_priv2wif(wif, priv);
    ASSERT_TRUE(ret);
    ASSERT_STREQ(WIF, wif);

    ret = btc_keys_priv2pub(pub, priv);
    ASSERT_TRUE(ret);
    ASSERT_EQ(0, memcmp(PUB, pub, sizeof(PUB)));

    ASSERT_TRUE(btc_keys_chkpub(pub));

    ret = btc_keys_pubuncomp(uncomppub, pub);
    ASSERT_TRUE(ret);
    ASSERT_EQ(0, memcmp(UNCOMPPUB, uncomppub, sizeof(UNCOMPPUB)));

    ret = btc_keys_pub2p2pkh(addr, pub);
    ASSERT_TRUE(ret);
    ASSERT_STREQ(ADDR, addr);

    ret = btc_keys_pub2p2wpkh(waddr, pub);
    ASSERT_TRUE(ret);
    ASSERT_STREQ(WADDR, waddr);

    int pref;
    ret = btc_keys_addr2pkh(pkh2, &pref, addr);
    ASSERT_TRUE(ret);
    ASSERT_EQ(0, memcmp(PKH, pkh2, sizeof(PKH)));
    ASSERT_EQ(BTC_PREF_P2PKH, pref);
}


TEST_F(keys, pub2uncomp)
{
    uint8_t uncomppub[BTC_SZ_PUBKEY_UNCOMP - 1];

    //https://gist.github.com/flying-fury/6bc42c8bb60e5ea26631
    const uint8_t COMP[][33] = {
        {   0x02, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98 },
        {   0x03, 0xF2, 0x87, 0x73, 0xC2, 0xD9, 0x75, 0x28, 0x8B, 0xC7, 0xD1, 0xD2, 0x05, 0xC3, 0x74, 0x86, 0x51, 0xB0, 0x75, 0xFB, 0xC6, 0x61, 0x0E, 0x58, 0xCD, 0xDE, 0xED, 0xDF, 0x8F, 0x19, 0x40, 0x5A, 0xA8 },
        {   0x02, 0xFE, 0x8D, 0x1E, 0xB1, 0xBC, 0xB3, 0x43, 0x2B, 0x1D, 0xB5, 0x83, 0x3F, 0xF5, 0xF2, 0x22, 0x6D, 0x9C, 0xB5, 0xE6, 0x5C, 0xEE, 0x43, 0x05, 0x58, 0xC1, 0x8E, 0xD3, 0xA3, 0xC8, 0x6C, 0xE1, 0xAF },
        {   0x03, 0x07, 0x92, 0x64, 0xC4, 0xB4, 0xBF, 0xCD, 0x7F, 0xE3, 0xA7, 0xB7, 0xB9, 0x2B, 0x6C, 0x43, 0x9F, 0x3A, 0x5B, 0x3A, 0xBC, 0xD2, 0x91, 0x89, 0xBF, 0x7B, 0x54, 0xD7, 0x81, 0xFF, 0x03, 0xD7, 0x22 },
    };

    const uint8_t UNCOMP[][64] = {
        {   /*0x04,*/ 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98, 0x48, 0x3A, 0xDA, 0x77, 0x26, 0xA3, 0xC4, 0x65, 0x5D, 0xA4, 0xFB, 0xFC, 0x0E, 0x11, 0x08, 0xA8, 0xFD, 0x17, 0xB4, 0x48, 0xA6, 0x85, 0x54, 0x19, 0x9C, 0x47, 0xD0, 0x8F, 0xFB, 0x10, 0xD4, 0xB8 },
        {   /*0x04,*/ 0xF2, 0x87, 0x73, 0xC2, 0xD9, 0x75, 0x28, 0x8B, 0xC7, 0xD1, 0xD2, 0x05, 0xC3, 0x74, 0x86, 0x51, 0xB0, 0x75, 0xFB, 0xC6, 0x61, 0x0E, 0x58, 0xCD, 0xDE, 0xED, 0xDF, 0x8F, 0x19, 0x40, 0x5A, 0xA8, 0x0A, 0xB0, 0x90, 0x2E, 0x8D, 0x88, 0x0A, 0x89, 0x75, 0x82, 0x12, 0xEB, 0x65, 0xCD, 0xAF, 0x47, 0x3A, 0x1A, 0x06, 0xDA, 0x52, 0x1F, 0xA9, 0x1F, 0x29, 0xB5, 0xCB, 0x52, 0xDB, 0x03, 0xED, 0x81 },
        {   /*0x04,*/ 0xFE, 0x8D, 0x1E, 0xB1, 0xBC, 0xB3, 0x43, 0x2B, 0x1D, 0xB5, 0x83, 0x3F, 0xF5, 0xF2, 0x22, 0x6D, 0x9C, 0xB5, 0xE6, 0x5C, 0xEE, 0x43, 0x05, 0x58, 0xC1, 0x8E, 0xD3, 0xA3, 0xC8, 0x6C, 0xE1, 0xAF, 0x07, 0xB1, 0x58, 0xF2, 0x44, 0xCD, 0x0D, 0xE2, 0x13, 0x4A, 0xC7, 0xC1, 0xD3, 0x71, 0xCF, 0xFB, 0xFA, 0xE4, 0xDB, 0x40, 0x80, 0x1A, 0x25, 0x72, 0xE5, 0x31, 0xC5, 0x73, 0xCD, 0xA9, 0xB5, 0xB4 },
        {   /*0x04,*/ 0x07, 0x92, 0x64, 0xC4, 0xB4, 0xBF, 0xCD, 0x7F, 0xE3, 0xA7, 0xB7, 0xB9, 0x2B, 0x6C, 0x43, 0x9F, 0x3A, 0x5B, 0x3A, 0xBC, 0xD2, 0x91, 0x89, 0xBF, 0x7B, 0x54, 0xD7, 0x81, 0xFF, 0x03, 0xD7, 0x22, 0x6F, 0x6F, 0x0E, 0x07, 0x84, 0xEA, 0xDA, 0x9F, 0x92, 0x99, 0x9E, 0xE9, 0xC4, 0x38, 0xD4, 0x7E, 0xAA, 0x2C, 0x80, 0x68, 0xF1, 0x84, 0x51, 0x97, 0xE3, 0x07, 0x1C, 0x74, 0xB0, 0x63, 0xC5, 0xE1 },
    };

    for (int lp = 0; lp < 4; lp++) {
        bool ret = btc_keys_pubuncomp(uncomppub, COMP[lp]);
        ASSERT_TRUE(ret);
        ASSERT_EQ(0, memcmp(UNCOMP[lp], uncomppub, sizeof(uncomppub)));
    }
}


#if 0
TEST_F(keys, pub2uncomp2)
{
    uint8_t uncomppub[BTC_SZ_PUBKEY_UNCOMP - 1];

    //http://bitcoin.stackexchange.com/questions/21974/need-sample-compressed-and-uncompressed-public-private-key-pairs-for-bigintege
    const uint8_t COMP[][33] = {
        {
            0x03, 0xA3, 0xD7, 0x00, 0x82, 0xD2, 0x3B, 0x32,
            0xB2, 0x68, 0x90, 0xEA, 0x01, 0xF6, 0xAF, 0x62,
            0x8F, 0x8D, 0x42, 0x4D, 0xF3, 0xB0, 0x25, 0x80,
            0x2D, 0x32, 0xFC, 0x3F, 0x2D, 0x5E, 0xF4, 0xD0,
            0x83,
        },
    };
//    const uint8_t UNCOMP[][64] = {
//        {
//
//        },
//    };

    for (int lp = 0; lp < 1; lp++) {
        bool ret = btc_keys_pubuncomp(uncomppub, COMP[lp]);
        ASSERT_TRUE(ret);
        //ASSERT_EQ(0, memcmp(UNCOMP[lp], uncomppub, sizeof(uncomppub)));
        keys::DumpBin(uncomppub, sizeof(uncomppub));
    }
}
#endif


TEST_F(keys, addr2pkh_fail1)
{
    //Base58ではない文字列
    const char ADDR[] = "*wJyBWTEUYMdJ12JWwK3eXff48pxQU6685";

    uint8_t pkh[BTC_SZ_PUBKEYHASH];

    int pref;
    bool ret = btc_keys_addr2pkh(pkh, &pref, ADDR);
    ASSERT_FALSE(ret);
}


TEST_F(keys, p2wpkh_addr)
{
    bool ret;
    const char ADDR[] = "mtLLAiafrhzcjSZqp2Ts86Gv7PupWnXKUc";
    char waddr[BTC_SZ_ADDR_STR_MAX + 1];
    ret = btc_keys_addr2p2wpkh(waddr, ADDR);
    ASSERT_TRUE(ret);
    ASSERT_STREQ("2NCFo5oZuEbXgZdMDzLMA2qQiroHrU6oXSU", waddr);     //bitcoindで計算した値
    printf(" addr= %s\n", ADDR);
    printf("waddr= %s\n", waddr);

    const char ADDR2[] = "mmsgPUnoceq7er7f9HuaZV2ktMkaVD3Za1";
    ret = btc_keys_addr2p2wpkh(waddr, ADDR2);
    ASSERT_TRUE(ret);
    ASSERT_STREQ("2NDxM8795n9HsLiniWowcn6gwSemNKzsN7a", waddr);     //bitcoindで計算した値
    printf(" addr= %s\n", ADDR2);
    printf("waddr= %s\n", waddr);
}


TEST_F(keys, multi_2of2_1)
{
    const uint8_t PUB1[] = {
        0x03, 0x24, 0x0b, 0xc7, 0x9a, 0x64, 0x79, 0x85,
        0x1a, 0xbe, 0x77, 0x64, 0x65, 0x50, 0x0a, 0x9f,
        0xf2, 0xf8, 0x80, 0x94, 0x0b, 0x22, 0x7b, 0xfc,
        0xbc, 0xb6, 0xd4, 0x79, 0x88, 0x6a, 0x31, 0x8f,
        0xa0,
    };
    const uint8_t PUB2[] = {
        0x03, 0x92, 0x1b, 0x52, 0x4e, 0x16, 0xb8, 0x1c,
        0x81, 0x3b, 0xaf, 0x06, 0x2a, 0x28, 0x44, 0xff,
        0x68, 0x42, 0x07, 0x3c, 0xc0, 0xec, 0x60, 0x92,
        0x31, 0xa0, 0xe3, 0x37, 0x00, 0xdd, 0x24, 0xb5,
        0xf3,
    };
    const uint8_t REDEEM[] = {
        0x52, 0x21, 0x03, 0x24, 0x0b, 0xc7, 0x9a, 0x64,
        0x79, 0x85, 0x1a, 0xbe, 0x77, 0x64, 0x65, 0x50,
        0x0a, 0x9f, 0xf2, 0xf8, 0x80, 0x94, 0x0b, 0x22,
        0x7b, 0xfc, 0xbc, 0xb6, 0xd4, 0x79, 0x88, 0x6a,
        0x31, 0x8f, 0xa0, 0x21, 0x03, 0x92, 0x1b, 0x52,
        0x4e, 0x16, 0xb8, 0x1c, 0x81, 0x3b, 0xaf, 0x06,
        0x2a, 0x28, 0x44, 0xff, 0x68, 0x42, 0x07, 0x3c,
        0xc0, 0xec, 0x60, 0x92, 0x31, 0xa0, 0xe3, 0x37,
        0x00, 0xdd, 0x24, 0xb5, 0xf3, 0x52, 0xae,
    };

    bool ret;
    utl_buf_t bufredeem;
    ret = btc_keys_create2of2(&bufredeem, PUB1, PUB2);
    //keys::DumpBin(bufredeem.buf, bufredeem.len);
    ASSERT_TRUE(ret);
    ASSERT_EQ(sizeof(REDEEM), bufredeem.len);
    ASSERT_EQ(0, memcmp(REDEEM, bufredeem.buf, sizeof(REDEEM)));
    utl_buf_free(&bufredeem);
}


#if 0   //ソートしないようにした
TEST_F(keys, multi_2of2_2)
{
    //PUB1とPUB2の順を逆にしても、ソートして同じREDEEMになる
    const uint8_t PUB1[] = {
        0x03, 0x24, 0x0b, 0xc7, 0x9a, 0x64, 0x79, 0x85,
        0x1a, 0xbe, 0x77, 0x64, 0x65, 0x50, 0x0a, 0x9f,
        0xf2, 0xf8, 0x80, 0x94, 0x0b, 0x22, 0x7b, 0xfc,
        0xbc, 0xb6, 0xd4, 0x79, 0x88, 0x6a, 0x31, 0x8f,
        0xa0,
    };
    const uint8_t PUB2[] = {
        0x03, 0x92, 0x1b, 0x52, 0x4e, 0x16, 0xb8, 0x1c,
        0x81, 0x3b, 0xaf, 0x06, 0x2a, 0x28, 0x44, 0xff,
        0x68, 0x42, 0x07, 0x3c, 0xc0, 0xec, 0x60, 0x92,
        0x31, 0xa0, 0xe3, 0x37, 0x00, 0xdd, 0x24, 0xb5,
        0xf3,
    };
    const uint8_t REDEEM[] = {
        0x52, 0x21, 0x03, 0x24, 0x0b, 0xc7, 0x9a, 0x64,
        0x79, 0x85, 0x1a, 0xbe, 0x77, 0x64, 0x65, 0x50,
        0x0a, 0x9f, 0xf2, 0xf8, 0x80, 0x94, 0x0b, 0x22,
        0x7b, 0xfc, 0xbc, 0xb6, 0xd4, 0x79, 0x88, 0x6a,
        0x31, 0x8f, 0xa0, 0x21, 0x03, 0x92, 0x1b, 0x52,
        0x4e, 0x16, 0xb8, 0x1c, 0x81, 0x3b, 0xaf, 0x06,
        0x2a, 0x28, 0x44, 0xff, 0x68, 0x42, 0x07, 0x3c,
        0xc0, 0xec, 0x60, 0x92, 0x31, 0xa0, 0xe3, 0x37,
        0x00, 0xdd, 0x24, 0xb5, 0xf3, 0x52, 0xae,
    };

    bool ret;
    utl_buf_t bufredeem;
    ret = btc_keys_create2of2(&bufredeem, PUB2, PUB1);
    //keys::DumpBin(bufredeem.buf, bufredeem.len);
    ASSERT_TRUE(ret);
    ASSERT_EQ(sizeof(REDEEM), bufredeem.len);
    ASSERT_EQ(0, memcmp(REDEEM, bufredeem.buf, sizeof(REDEEM)));
    utl_buf_free(&bufredeem);
}


TEST_F(keys, multi_2of2_same)
{
    //PUB1とPUB2の順を逆にしても、ソートして同じREDEEMになる
    const uint8_t PUB1[] = {
        0x03, 0x24, 0x0b, 0xc7, 0x9a, 0x64, 0x79, 0x85,
        0x1a, 0xbe, 0x77, 0x64, 0x65, 0x50, 0x0a, 0x9f,
        0xf2, 0xf8, 0x80, 0x94, 0x0b, 0x22, 0x7b, 0xfc,
        0xbc, 0xb6, 0xd4, 0x79, 0x88, 0x6a, 0x31, 0x8f,
        0xa0,
    };

    bool ret;
    utl_buf_t bufredeem;
    ret = btc_keys_create2of2(&bufredeem, PUB1, PUB1);
    ASSERT_FALSE(ret);
    //utl_buf_free(&bufredeem);
}
#endif


TEST_F(keys, multi_2of3)
{
    const uint8_t PUB1[] = {
        0x03, 0x24, 0x0b, 0xc7, 0x9a, 0x64, 0x79, 0x85,
        0x1a, 0xbe, 0x77, 0x64, 0x65, 0x50, 0x0a, 0x9f,
        0xf2, 0xf8, 0x80, 0x94, 0x0b, 0x22, 0x7b, 0xfc,
        0xbc, 0xb6, 0xd4, 0x79, 0x88, 0x6a, 0x31, 0x8f,
        0xa0,
    };
    const uint8_t PUB2[] = {
        0x03, 0x92, 0x1b, 0x52, 0x4e, 0x16, 0xb8, 0x1c,
        0x81, 0x3b, 0xaf, 0x06, 0x2a, 0x28, 0x44, 0xff,
        0x68, 0x42, 0x07, 0x3c, 0xc0, 0xec, 0x60, 0x92,
        0x31, 0xa0, 0xe3, 0x37, 0x00, 0xdd, 0x24, 0xb5,
        0xf3,
    };
    const uint8_t PUB3[] = {
        0x03, 0x29, 0xbd, 0x4a, 0x08, 0x25, 0x0b, 0x6a,
        0xef, 0x97, 0x58, 0x1b, 0x36, 0x41, 0x2c, 0x9b,
        0xe2, 0x8c, 0x84, 0xba, 0xb7, 0x7d, 0x7a, 0x51,
        0x8a, 0x88, 0x00, 0x3a, 0x18, 0x0a, 0xfc, 0xfc,
        0xdc,
    };
    const uint8_t *PUBS[] = {
        PUB1, PUB2, PUB3
    };
    const uint8_t REDEEM[] = {
        0x52, 0x21, 0x03, 0x24, 0x0b, 0xc7, 0x9a, 0x64,
        0x79, 0x85, 0x1a, 0xbe, 0x77, 0x64, 0x65, 0x50,
        0x0a, 0x9f, 0xf2, 0xf8, 0x80, 0x94, 0x0b, 0x22,
        0x7b, 0xfc, 0xbc, 0xb6, 0xd4, 0x79, 0x88, 0x6a,
        0x31, 0x8f, 0xa0, 0x21, 0x03, 0x92, 0x1b, 0x52,
        0x4e, 0x16, 0xb8, 0x1c, 0x81, 0x3b, 0xaf, 0x06,
        0x2a, 0x28, 0x44, 0xff, 0x68, 0x42, 0x07, 0x3c,
        0xc0, 0xec, 0x60, 0x92, 0x31, 0xa0, 0xe3, 0x37,
        0x00, 0xdd, 0x24, 0xb5, 0xf3, 0x21, 0x03, 0x29,
        0xbd, 0x4a, 0x08, 0x25, 0x0b, 0x6a, 0xef, 0x97,
        0x58, 0x1b, 0x36, 0x41, 0x2c, 0x9b, 0xe2, 0x8c,
        0x84, 0xba, 0xb7, 0x7d, 0x7a, 0x51, 0x8a, 0x88,
        0x00, 0x3a, 0x18, 0x0a, 0xfc, 0xfc, 0xdc, 0x53,
        0xae,
    };

    utl_buf_t bufredeem;
    bool ret = btc_keys_createmulti(&bufredeem, PUBS, 3, 2);
    //keys::DumpBin(bufredeem.buf, bufredeem.len);
    ASSERT_TRUE(ret);
    ASSERT_EQ(sizeof(REDEEM), bufredeem.len);
    ASSERT_EQ(0, memcmp(REDEEM, bufredeem.buf, sizeof(REDEEM)));
    utl_buf_free(&bufredeem);
}


TEST_F(keys, wit2p2wsh)
{
    const uint8_t REDEEM[] = {
        0x52, 0x21, 0x03, 0xd7, 0x98, 0x23, 0x4d, 0xf0,
        0x07, 0xfe, 0x4d, 0x6f, 0x9c, 0x08, 0xeb, 0x5a,
        0x81, 0xc7, 0xca, 0xe1, 0x06, 0x38, 0xa0, 0xe6,
        0xc8, 0x40, 0xad, 0x80, 0xfd, 0x56, 0xf1, 0x32,
        0xa2, 0x4c, 0xaf, 0x21, 0x02, 0x1c, 0x5f, 0x25,
        0x61, 0x40, 0x24, 0x56, 0xcc, 0x46, 0x8f, 0xac,
        0x15, 0xe2, 0x15, 0x2d, 0xf0, 0x32, 0x2b, 0x74,
        0xef, 0xe9, 0x33, 0xce, 0x21, 0x2b, 0x08, 0x42,
        0xb4, 0x76, 0x77, 0x5d, 0x22, 0x21, 0x03, 0x06,
        0x84, 0xb3, 0x3c, 0xde, 0x5a, 0xd6, 0x80, 0x69,
        0x76, 0x22, 0x1a, 0x8e, 0xac, 0x18, 0x33, 0xf6,
        0x43, 0x23, 0x95, 0x03, 0xbf, 0x4b, 0x19, 0xe6,
        0x18, 0x2e, 0x82, 0x04, 0x95, 0x3e, 0x74, 0x53,
        0xae,
    };
    const utl_buf_t wit = { (uint8_t *)REDEEM, sizeof(REDEEM) };
    const char ADDR[] = "2Mt8fd67GgFMQpeKqn9mZ6VRWHnK6MAzGbD";

    char addr[BTC_SZ_ADDR_STR_MAX + 1];
    bool ret = btc_keys_wit2waddr(addr, &wit);
    ASSERT_TRUE(ret);
    ASSERT_STREQ(ADDR, addr);
}


TEST_F(keys, uncomp1)
{
    const uint8_t COMP[] = {
        0x02, 0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98
    };
    const uint8_t UNCOMP[] = {
        0x79, 0xBE, 0x66, 0x7E, 0xF9, 0xDC, 0xBB, 0xAC, 0x55, 0xA0, 0x62, 0x95, 0xCE, 0x87, 0x0B, 0x07, 0x02, 0x9B, 0xFC, 0xDB, 0x2D, 0xCE, 0x28, 0xD9, 0x59, 0xF2, 0x81, 0x5B, 0x16, 0xF8, 0x17, 0x98, 0x48, 0x3A, 0xDA, 0x77, 0x26, 0xA3, 0xC4, 0x65, 0x5D, 0xA4, 0xFB, 0xFC, 0x0E, 0x11, 0x08, 0xA8, 0xFD, 0x17, 0xB4, 0x48, 0xA6, 0x85, 0x54, 0x19, 0x9C, 0x47, 0xD0, 0x8F, 0xFB, 0x10, 0xD4, 0xB8
    };
    mbedtls_ecp_point unpnt;
    uint8_t uncomp[BTC_SZ_PUBKEY_UNCOMP - 1];

    mbedtls_ecp_point_init(&unpnt);
    int ret = btc_util_ecp_point_read_binary2(&unpnt, COMP);
    ASSERT_EQ(0, ret);
    mbedtls_mpi_write_binary(&unpnt.X, uncomp, 32);
    mbedtls_mpi_write_binary(&unpnt.Y, uncomp + 32, 32);
    mbedtls_ecp_point_free(&unpnt);
    ASSERT_EQ(0, memcmp(UNCOMP, uncomp, 64));
}


TEST_F(keys, uncomp2)
{
    const uint8_t COMP[] = {
        0x03, 0xF2, 0x87, 0x73, 0xC2, 0xD9, 0x75, 0x28, 0x8B, 0xC7, 0xD1, 0xD2, 0x05, 0xC3, 0x74, 0x86, 0x51, 0xB0, 0x75, 0xFB, 0xC6, 0x61, 0x0E, 0x58, 0xCD, 0xDE, 0xED, 0xDF, 0x8F, 0x19, 0x40, 0x5A, 0xA8
    };
    const uint8_t UNCOMP[] = {
        0xF2, 0x87, 0x73, 0xC2, 0xD9, 0x75, 0x28, 0x8B, 0xC7, 0xD1, 0xD2, 0x05, 0xC3, 0x74, 0x86, 0x51, 0xB0, 0x75, 0xFB, 0xC6, 0x61, 0x0E, 0x58, 0xCD, 0xDE, 0xED, 0xDF, 0x8F, 0x19, 0x40, 0x5A, 0xA8, 0x0A, 0xB0, 0x90, 0x2E, 0x8D, 0x88, 0x0A, 0x89, 0x75, 0x82, 0x12, 0xEB, 0x65, 0xCD, 0xAF, 0x47, 0x3A, 0x1A, 0x06, 0xDA, 0x52, 0x1F, 0xA9, 0x1F, 0x29, 0xB5, 0xCB, 0x52, 0xDB, 0x03, 0xED, 0x81
    };
    mbedtls_ecp_point unpnt;
    uint8_t uncomp[BTC_SZ_PUBKEY_UNCOMP - 1];

    mbedtls_ecp_point_init(&unpnt);
    int ret = btc_util_ecp_point_read_binary2(&unpnt, COMP);
    ASSERT_EQ(0, ret);
    mbedtls_mpi_write_binary(&unpnt.X, uncomp, 32);
    mbedtls_mpi_write_binary(&unpnt.Y, uncomp + 32, 32);
    mbedtls_ecp_point_free(&unpnt);
    ASSERT_EQ(0, memcmp(UNCOMP, uncomp, 64));
}


TEST_F(keys, uncomp3)
{
    const uint8_t COMP[] = {
        0x02, 0xFE, 0x8D, 0x1E, 0xB1, 0xBC, 0xB3, 0x43, 0x2B, 0x1D, 0xB5, 0x83, 0x3F, 0xF5, 0xF2, 0x22, 0x6D, 0x9C, 0xB5, 0xE6, 0x5C, 0xEE, 0x43, 0x05, 0x58, 0xC1, 0x8E, 0xD3, 0xA3, 0xC8, 0x6C, 0xE1, 0xAF
    };
    const uint8_t UNCOMP[] = {
        0xFE, 0x8D, 0x1E, 0xB1, 0xBC, 0xB3, 0x43, 0x2B, 0x1D, 0xB5, 0x83, 0x3F, 0xF5, 0xF2, 0x22, 0x6D, 0x9C, 0xB5, 0xE6, 0x5C, 0xEE, 0x43, 0x05, 0x58, 0xC1, 0x8E, 0xD3, 0xA3, 0xC8, 0x6C, 0xE1, 0xAF, 0x07, 0xB1, 0x58, 0xF2, 0x44, 0xCD, 0x0D, 0xE2, 0x13, 0x4A, 0xC7, 0xC1, 0xD3, 0x71, 0xCF, 0xFB, 0xFA, 0xE4, 0xDB, 0x40, 0x80, 0x1A, 0x25, 0x72, 0xE5, 0x31, 0xC5, 0x73, 0xCD, 0xA9, 0xB5, 0xB4
    };
    mbedtls_ecp_point unpnt;
    uint8_t uncomp[BTC_SZ_PUBKEY_UNCOMP - 1];

    mbedtls_ecp_point_init(&unpnt);
    int ret = btc_util_ecp_point_read_binary2(&unpnt, COMP);
    ASSERT_EQ(0, ret);
    mbedtls_mpi_write_binary(&unpnt.X, uncomp, 32);
    mbedtls_mpi_write_binary(&unpnt.Y, uncomp + 32, 32);
    mbedtls_ecp_point_free(&unpnt);
    ASSERT_EQ(0, memcmp(UNCOMP, uncomp, 64));
}


TEST_F(keys, uncomp4)
{
    const uint8_t COMP[] = {
        0x03, 0x07, 0x92, 0x64, 0xC4, 0xB4, 0xBF, 0xCD, 0x7F, 0xE3, 0xA7, 0xB7, 0xB9, 0x2B, 0x6C, 0x43, 0x9F, 0x3A, 0x5B, 0x3A, 0xBC, 0xD2, 0x91, 0x89, 0xBF, 0x7B, 0x54, 0xD7, 0x81, 0xFF, 0x03, 0xD7, 0x22
    };
    const uint8_t UNCOMP[] = {
        0x07, 0x92, 0x64, 0xC4, 0xB4, 0xBF, 0xCD, 0x7F, 0xE3, 0xA7, 0xB7, 0xB9, 0x2B, 0x6C, 0x43, 0x9F, 0x3A, 0x5B, 0x3A, 0xBC, 0xD2, 0x91, 0x89, 0xBF, 0x7B, 0x54, 0xD7, 0x81, 0xFF, 0x03, 0xD7, 0x22, 0x6F, 0x6F, 0x0E, 0x07, 0x84, 0xEA, 0xDA, 0x9F, 0x92, 0x99, 0x9E, 0xE9, 0xC4, 0x38, 0xD4, 0x7E, 0xAA, 0x2C, 0x80, 0x68, 0xF1, 0x84, 0x51, 0x97, 0xE3, 0x07, 0x1C, 0x74, 0xB0, 0x63, 0xC5, 0xE1
    };
    mbedtls_ecp_point unpnt;
    uint8_t uncomp[BTC_SZ_PUBKEY_UNCOMP - 1];

    mbedtls_ecp_point_init(&unpnt);
    int ret = btc_util_ecp_point_read_binary2(&unpnt, COMP);
    ASSERT_EQ(0, ret);
    mbedtls_mpi_write_binary(&unpnt.X, uncomp, 32);
    mbedtls_mpi_write_binary(&unpnt.Y, uncomp + 32, 32);
    mbedtls_ecp_point_free(&unpnt);
    ASSERT_EQ(0, memcmp(UNCOMP, uncomp, 64));
}
