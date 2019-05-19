#ifndef QPACKET_H
#define QPACKET_H

#include <QObject>
#include <QIODevice>
#include <QSysInfo>
#include <QDataStream>

class QPacket
{
private:
    QDataStream             *m_pDataStream;

protected:
    QByteArray              *m_pbtarrayData;
    QIODevice               *m_pDevice;

public:
                            QPacket(QByteArray *data, QDataStream::ByteOrder byteOrder = QDataStream::LittleEndian, QIODevice *device = nullptr);

    void                    setByteOrder(QDataStream::ByteOrder byteOrder);
    QDataStream::ByteOrder  getByteOrder();
    int                     getPacketSize();

    void                    writeInt32Data(qint32 data);
    void                    writeDoubleData(double data);
    void                    writeWStringData(const ushort *data, int len);
    void                    writeWStringData(QString string);

    void                    setPacketLengthField();
    QByteArray*             getPacketData();

    qint64                  flushData();
};

#endif // QPACKET_H
