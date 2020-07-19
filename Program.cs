public class Pattern
{
    private ProcessModule processModule;
    private string pattern;

    public Pattern(ProcessModule _processModule, string _pattern)
    {
        processModule = _processModule;
        pattern = _pattern;
    }

    private bool checkPattern(string pattern, byte[] array2check)
    {
        int len = array2check.Length;
        string[] strBytes = pattern.Split(' ');
        int x = 0;
        foreach (byte b in array2check)
        {
            if (strBytes[x] == "?" || strBytes[x] == "??")
            {
                x++;
            }
            else if (byte.Parse(strBytes[x], NumberStyles.HexNumber) == b)
            {
                x++;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    public List<IntPtr> Adress
    {
        get
        {
            byte[] moduleMemory = new Pointer<byte[]>(processModule.BaseAddress, processModule.ModuleMemorySize).ReadValue();
            string[] splitPattern = pattern.Split(' ');
            List<IntPtr> adressList = new List<IntPtr>();
            try
            {
                for (int y = 0; y < moduleMemory.Length; y++)
                {
                    if (moduleMemory[y] == byte.Parse(splitPattern[0], NumberStyles.HexNumber))
                    {
                        byte[] checkArray = new byte[splitPattern.Length];
                        for (int x = 0; x < splitPattern.Length; x++)
                        {
                            checkArray[x] = moduleMemory[y + x];
                        }
                        if (checkPattern(pattern, checkArray))
                        {
                            adressList.Add((IntPtr)((uint)processModule.BaseAddress + y));
                        }
                        else
                        {
                            y += splitPattern.Length - (splitPattern.Length / 2);
                        }
                    }
                }
                return adressList;
            }
            catch (Exception)
            {
                throw new Exception("Could not check the pattern");
            }
        }
    }

}

class Test
{
    public Test()
    {
        IntPtr adress = new Pattern(Process.GetProcesses().First().MainModule, "f3 0f 11 86 ? ? ? ? 76 1d f3 0f 5e c1 f3 0f 11 45 08").Adress.First();
    }
}