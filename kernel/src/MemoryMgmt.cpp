int last_index;
void removeCache()
{
}
void move_mem(int from, int to, int till)
{
	char *from_c = (char *)0x0 + from;
	char *to_c = (char *)0x0 + to;
	for (int i = 0; i < till; i++)
	{
		to_c[i] = from_c[i];
	}
}
void memory_init()
{
	last_index = 0xFFFFFF;
	char *tempr = (char *)last_index;
}
void roll_back(int to)
{
	last_index -= to;
}
int getMemPointer()
{
	return last_index;
}