
#include <stdio.h>
#include <stdlib.h>

// �ҵ�IDA��һֱ˵�Ҳ���MS DIA SDK����������������װ�ˣ�vs2017, vs2008
// ���ʵ��û�취����Ϊrelease�汾�ǿ��Կ����ŵģ�����release�汾�У��ر�
// �˱������Ż�
#pragma optimize( "", off )
int test_assign()
{
    int a;

    a = 0x1234;

    return a;
}
#pragma optimize( "", on )

int main()
{
    int a = 0;

    a = test_assign();

    printf("%d\n", a);

    return a + 1;
}