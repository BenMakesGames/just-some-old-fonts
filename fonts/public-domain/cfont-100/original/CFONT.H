/*
*	CFONT.H - ColorFont class definition
*	==================================================================
*	Written by Nikolai Soumarokov
*	Version 1.00, July 7, 1995
*	See the CFONT.DOC file for description of functions and variables
*/


class ColorFont {

private:
      // private variables
      unsigned char *Font_Buffer;
      unsigned char far *Video_Address;
      unsigned int Clip_Top;
      unsigned int Clip_Bottom;
      unsigned int Clip_Left;
      unsigned int Clip_Right;
      unsigned int VScreen_Width;
      unsigned int VScreen_Height;
      unsigned char Translation[256];

public:
      // public variables
      int Font_NumOfChars;
      int Font_CharWidth;
      int Font_CharHeight;
      int Horiz_Spacing;
      int Vert_Spacing;

      // public functions
      ColorFont (char *);
      ~ColorFont ();
      void SetVideoAddress(unsigned char far *);
      void SetVideoAddress();
      void SetVScreenDim(unsigned int, unsigned int);
      void SetClipArea(unsigned int, unsigned int, unsigned int, unsigned int);
      void SetClipArea();
      void SetSpacing(int, int);
      void SetSpacing(int);
      void SetSpacing();

      void SetTranslation(char *);
      void SetSameChar(char, char);

      void ChangeColor(unsigned char, unsigned char);
      void Repaint(int, ...);

      void PutCh(int, int, char);
      void BPutCh(int, int, char);
      void CPutCh(int, int, char);
      void CBPutCh(int, int, char);

      void Print(int, int, char *);
      void BPrint(int, int, char *);
      void CPrint(int, int, char *);
      void CBPrint(int, int, char *);
};
