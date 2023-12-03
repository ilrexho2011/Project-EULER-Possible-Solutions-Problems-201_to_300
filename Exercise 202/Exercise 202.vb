Dim b As New Bitmap(1000, 701)
    Dim g As Graphics = Graphics.FromImage(b)
    Private Sub TrackBar1_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TrackBar1.Scroll
        g.FillRectangle(Brushes.White, 0, 0, 1000, 701)
        g.DrawLine(Pens.Black, 500, 0, 500 + Integer.Parse(Int(700 / Math.Sqrt(3))), 700)
        g.DrawLine(Pens.Black, 500, 0, 500 - Integer.Parse(Int(700 / Math.Sqrt(3))), 700)
        g.DrawLine(Pens.Black, 500 - Integer.Parse(Int(700 / Math.Sqrt(3))), 700, 500 + Integer.Parse(Int(700 / Math.Sqrt(3))), 700)
        Dim x1 As Double, y1 As Double, x2 As Double, y2 As Double, x3 As Double, y3 As Double, x0 As Double, y0 As Double
        Dim a1 As Double, b1 As Double, a2 As Double, b2 As Double, a3 As Double, b3 As Double, a0 As Double, b0 As Double
        Dim c As Double, d As Double, f As Double, a As Double, h As Double
        Dim j As Integer, k As Integer, l As Integer, m As Integer
        x1 = 500
        y1 = 0
        a1 = 700 / Math.Sqrt(3)
        b1 = 700
        x2 = 500
        y2 = 0
        a2 = -700 / Math.Sqrt(3)
        b2 = 700
        x3 = 500 - 700 / Math.Sqrt(3)
        y3 = 700
        a3 = 1400 / Math.Sqrt(3)
        b3 = 0
        x0 = 500
        y0 = 0
        b0 = Math.Cos(TrackBar1.Value / 180000 * Math.PI)
        a0 = Math.Sin(TrackBar1.Value / 180000 * Math.PI)
        Dim q As Integer = TrackBar2.Value * 2
        For i = 1 To q
            c = 1
            d = 1
            f = 1
            a = x0
            h = y0
            If a1 * b0 - b1 * a0 <> 0 Then c = ((x0 - x1) * b0 - (y0 - y1) * a0) / (a1 * b0 - b1 * a0)
            If a2 * b0 - b2 * a0 <> 0 Then d = ((x0 - x2) * b0 - (y0 - y2) * a0) / (a2 * b0 - b2 * a0)
            If a3 * b0 - b3 * a0 <> 0 Then f = ((x0 - x3) * b0 - (y0 - y3) * a0) / (a3 * b0 - b3 * a0)
            If c <= 0 Or j = 1 Then c = 1
            If d <= 0 Or j = 2 Then d = 1
            If f <= 0 Or j = 3 Then f = 1
            If d < c Then
                If f < d Then
                    x0 = x3 + a3 * f
                    y0 = y3 + b3 * f
                    b0 = -b0
                    j = 3
                    m += 1
                Else
                    x0 = x2 + a2 * d
                    y0 = y2 + b2 * d
                    c = -(b0 * a2 - a0 * b2) / (a2 * a2 + b2 * b2)
                    d = (a0 * a2 + b0 * b2) / (a2 * a2 + b2 * b2)
                    a0 = -c * b2 + d * a2
                    b0 = c * a2 + d * b2
                    j = 2
                    l += 1
                End If
            Else
                If f < c Then
                    x0 = x3 + a3 * f
                    y0 = y3 + b3 * f
                    b0 = -b0
                    j = 3
                    m += 1
                Else
                    x0 = x1 + a1 * c
                    y0 = y1 + b1 * c
                    c = -(b0 * a1 - a0 * b1) / (a1 * a1 + b1 * b1)
                    d = (a0 * a1 + b0 * b1) / (a1 * a1 + b1 * b1)
                    a0 = -c * b1 + d * a1
                    b0 = c * a1 + d * b1
                    j = 1
                    k += 1
                End If
            End If
            If i = q Then
                g.DrawLine(Pens.Red, Integer.Parse(Int(a)), Integer.Parse(Int(h)), Integer.Parse(Int(x0)), Integer.Parse(Int(y0)))
            Else
                g.DrawLine(Pens.Black, Integer.Parse(Int(a)), Integer.Parse(Int(h)), Integer.Parse(Int(x0)), Integer.Parse(Int(y0)))
            End If
        Next
        Me.Text = k & " " & l & " " & m
        PictureBox1.Image = b
    End Sub

    Private Sub TrackBar2_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TrackBar2.Scroll
        Label1.Text = TrackBar2.Value * 2
    End Sub