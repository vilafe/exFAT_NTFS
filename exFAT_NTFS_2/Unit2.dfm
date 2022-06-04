object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Find Some'
  ClientHeight = 350
  ClientWidth = 340
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 32
    Top = 24
    Width = 117
    Height = 16
    Caption = 'Enter partition label:'
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 24
    Top = 64
    Width = 287
    Height = 209
    Header.AutoSizeIndex = -1
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = 'id'
        Width = 67
      end
      item
        Position = 1
        Text = 'signature'
        Width = 102
      end
      item
        Position = 2
        Text = 'sector'
        Width = 84
      end>
  end
  object Edit1: TEdit
    Left = 168
    Top = 21
    Width = 143
    Height = 24
    TabOrder = 1
    Text = 'E'
  end
  object Button1: TButton
    Left = 24
    Top = 279
    Width = 89
    Height = 25
    Caption = 'Analyze'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 24
    Top = 310
    Width = 89
    Height = 25
    Caption = 'Stop analyze'
    TabOrder = 3
    OnClick = Button2Click
  end
end
