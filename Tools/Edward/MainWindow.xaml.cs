using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Edward
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            Random r = new();
            InitializeComponent();
            for (int i = 0; i < 20; i++)
            {

                var bmp = new BitmapImage();
                bmp.BeginInit();
                bmp.UriSource = new Uri("https://picsum.photos/64/64?rnd=" + r.Next(), UriKind.Absolute);
                bmp.EndInit();

                TileArea.Children.Add(new Image()
                {
                    Style = (Style)FindResource("Tile"),
                    Source = bmp
                });
            }
        }
    }
}
