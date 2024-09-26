#pragma once

namespace kgr {

/**
 * @brief 异或校验
 *
 * @param buf 要校验的数据
 * @param len 数据长度
 * @return unsigned char
 */
unsigned char bcc_check_8(unsigned char *buf, unsigned int len);

/**
 * @brief crc16 校验
 *
 * @param data 需校验数据
 * @param len 数据长度
 * @return unsigned short 计算后的 crc16 校验码
 */
unsigned short crc16_xmodem(unsigned char *data, unsigned short len);

} // namespace kgr