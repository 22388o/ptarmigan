#!/bin/sh

# �`���l�����N���[�Y����B
# ���̂Ƃ���AMutual Close�̂ݎ������Ă���B
# P2PKH�A�h���X�ɑ������Ă��邽�߁Abitcoind�Ō��o�\�Ȃ͂��ł���B
#
# �`���l������Ă��m�[�h�Ƃ��ċ@�\���邽�߁Aucoind�͋N�������܂܂ɂȂ�B
# DB����̃`���l�����폜�́Agettxout �ɂ���� funding_tx�� unspent�ł͂Ȃ��Ȃ������Ƃ��m�F���Ă���s���Ă���B
./ucoincli -c conf/peer3333.conf -x 4444
./ucoincli -c conf/peer3333.conf -x 5555
