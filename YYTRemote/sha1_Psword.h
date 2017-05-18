#include "sha1.h"
#include <QString>

QString encryptPsword(QString&  strPs, QString& strEncrypt)
{
	SHA1Context sha;
	int i, err;
	uint8_t Message_Digest[20];


	err = SHA1Reset(&sha);	//·µ»Ø0

	if (err)
	{
		fprintf(stderr, "SHA1Reset Error %d.\n", err );
		return 0;
	}

	err = SHA1Input(&sha, (const unsigned char *)strPs.toStdString().c_str(), strPs.size());

	if (err)
	{
		fprintf(stderr, "SHA1Input Error %d.\n", err );
		return 0;
	}

	err = SHA1Result(&sha, Message_Digest);

	if (err)
	{
		fprintf(stderr,
			"SHA1Result Error %d, could not compute message digest.\n",
			err );
	}

	else
	{	
		for(i = 0; i < 20 ; ++i)
		{
			strEncrypt += QString("%1").arg(QString::number(Message_Digest[i], 16), 2, QChar('0'));
		}
	}

	return 0;
}