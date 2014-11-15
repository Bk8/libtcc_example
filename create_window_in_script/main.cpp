
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libtcc.h>

extern "C" void get_text(char* str)
{
	strcpy(str,"Hello tcc!");
}

int main(int argc, char **argv)
{
    TCCState *s;
    int (*script_main)(void);

	//�½�һ��TCCState
    s = tcc_new();
    if (!s)
	{
        fprintf(stderr, "Could not create tcc state\n");
        exit(1);
    }

	// ���ɵĴ���ŵ��ڴ��У��������ļ�
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

	// ��Ӵ�������Ҫ�õ���lib�ļ�
	tcc_add_file(s,"./lib/user32.def");
	tcc_add_file(s,"./lib/gdi32.def");
    tcc_add_symbol(s, "get_text", get_text);

	// ���Ҫִ�е�C�����ļ�
    if (tcc_add_file(s,"hello_win.c") == -1)
        return 1;

	// �ĵ���˵��ִ��tcc_get_symbol֮ǰ�����ȵ���һ����������������Ҿ�������
    if (tcc_relocate(s, TCC_RELOCATE_AUTO) < 0)
        return 1;
	// ��ȡ���ű��е�script_main����
    script_main = (int (*)(void))tcc_get_symbol(s, "script_main");
    if (!script_main)
        return 1;
	// ִ������
    script_main();

	// �����ֳ�
    tcc_delete(s);

    return 0;
}
