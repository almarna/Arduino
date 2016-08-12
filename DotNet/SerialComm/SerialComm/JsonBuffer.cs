using System.Text;

namespace SerialComm
{
    public class JsonBuffer
    {
        public string Last { get; private set; }

        private StringBuilder buffer = new StringBuilder();

        private int startBraces = 0;
        private int endBraces = 0;

        public JsonBuffer()
        {
            Last = string.Empty;
        }


        public bool AddChar(char character)
        {
            if (character == '{')
            {
                startBraces++;
            }

            if (startBraces < 1)
            {
                return false;
            }

            if (character == '}')
            {
                endBraces++;
            }

            buffer.Append(character);

            if (endBraces > 0 && startBraces == endBraces)
            {
                Last = buffer.ToString();
                ResetBuffer();
                return true;
            }
            else if (endBraces > startBraces)
            {
                //todo: handle error
                ResetBuffer();
                return false;
            }
            else
            {
                return false;
            }
        }

        public void ResetBuffer()
        {
            startBraces = 0;
            endBraces = 0;
            buffer.Clear();
        }

    }
}