object Form2: TForm2
  Left = 0
  Top = 0
  ActiveControl = VirtualStringTree1
  Caption = 'Wylian LAB 6'
  ClientHeight = 228
  ClientWidth = 317
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
    Width = 52
    Height = 16
    Caption = 'Partition:'
  end
  object VirtualStringTree1: TVirtualStringTree
    Left = 8
    Top = 93
    Width = 300
    Height = 124
    Header.AutoSizeIndex = -1
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Width = 67
      end
      item
        Position = 1
        Width = 102
      end
      item
        Position = 2
        Width = 84
      end>
  end
  object Edit1: TEdit
    Left = 90
    Top = 21
    Width = 143
    Height = 24
    TabOrder = 1
    Text = 'W:\'
  end
  object Button1: TButton
    Left = 33
    Top = 62
    Width = 89
    Height = 25
    Caption = 'Start'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 128
    Top = 62
    Width = 89
    Height = 25
    Caption = 'Stop'
    TabOrder = 3
    OnClick = Button2Click
  end
end