#include "qpacket.h"

QPacket::QPacket(QByteArray *data, QDataStream::ByteOrder byteOrder, QIODevice *device)
{
    m_pbtarrayData = data;
    m_pDevice = device;

    m_pDataStream = new QDataStream(m_pbtarrayData, QIODevice::ReadWrite);
    m_pDataStream->setByteOrder(byteOrder);
    qint32 nReserve = 0;
    m_pDataStream->operator<<(nReserve); // for pre-allocated length feild of which type is qint32
}

void QPacket::setByteOrder(QDataStream::ByteOrder byteOrder)
{
    m_pDataStream->setByteOrder(byteOrder);
}

QDataStream::ByteOrder QPacket::getByteOrder()
{
    return m_pDataStream->byteOrder();
}

void QPacket::setPacketLengthField()
{
    QIODevice *pDevice = m_pDataStream->device();
    qint64 nCurPos = pDevice->pos();
    pDevice->seek(0);
    qint32 nLen = m_pbtarrayData->length();
    m_pDataStream->operator<<(nLen);
    pDevice->seek(nCurPos);
}

void QPacket::writeInt32Data(qint32 data)
{
    m_pDataStream->operator<<(data);
}

void QPacket::writeDoubleData(double data)
{
    m_pDataStream->operator<<(data);
}

void QPacket::writeWStringData(const ushort *data, int len)
{
    for (int nI = 0; nI < len; ++nI)
        m_pDataStream->operator<<(data[nI]);

    ushort unTerminate = 0;
    m_pDataStream->operator<<(unTerminate);
}

void QPacket::writeWStringData(QString string)
{
    writeWStringData(string.utf16(), string.length());
}

QByteArray * QPacket::getPacketData()
{
    return m_pbtarrayData;
}

int QPacket::getPacketSize()
{
    return m_pbtarrayData->size();
}

qint64 QPacket::flushData()
{
    return m_pDevice->write(*m_pbtarrayData);
}
