using iText.Kernel.Pdf.Canvas.Parser;
using iText.Kernel.Pdf;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Drawing;

namespace pdfToText
{
    class PdfOpener
    {
        private Dictionary<string, List<string>> DATA = new Dictionary<string, List<string>>();
        private List<string> date = new List<string>();
        private List<string> RDNmonthly = new List<string>();
        private List<string> RDNvolume = new List<string>();
        private List<string> RDNhours = new List<string>();
        private List<string> Contracts = new List<string>();
        private List<string> Peaks = new List<string>();
        private List<string> PMOZE_A = new List<string>();
        private List<string> PMOZE_BIO = new List<string>();
        private List<string> PMEF_F = new List<string>();
        private List<string> PMOZE_AcontractsBil = new List<string>();
        private List<string> PMOZE_BIOcontractsBil = new List<string>();
        private List<string> PMEF_FcontractsBil = new List<string>();

        public int fails = 0;

        private string[][][] Patterns = {
            [
                [
                    @"(?<=BASE_WAvg \(PLN\/MWh\) \|\| [\d,-]+\n)[\d, ]{6,8}(?= )",
                    @"(?<=BASE_WAvg \(PLN\/MWh\) \|\| )[\d, ]{6,8}(?= )",
                    @"(?<=BASE \(PLN\/MWh\) \|\| [\d,-]+\n)[\d, ]{6,8}(?= )",
                    @"(?<=BASE \(PLN\/MWh\) \|\| )[\d, ]{6,8}(?= )",
                ],
                [
                    @"(?<=BASE price \(EUR\/MWh\) \|\| [\d, -]+\n)[\d, ]{5,8}(?= )",
                    @"(?<=BASE price \(EUR\/MWh\) \|\| )[\d, ]{5,8}(?= )",
                ],
                [
                    @"(?<= PEAK \(PLN\/MWh\) \|\| [\d, ]+ \|\| [\d, -]+ \|\| [\d]+\n)[\d, ]{6,8}(?=\n)",
                    @"(?<= PEAK \(PLN\/MWh\) \|\| [\d, ]+ \|\| [\d, -]+\n)[\d, ]{6,8}(?=\n)",
                    @"(?<= PEAK \(PLN\/MWh\) \|\| )[\d, ]{6,8}(?= )"
                ],
                [
                    @"(?<= PEAK Price \(EUR\/MWh\) \|\| [\d, -]+ \|\| [\d]+\n)[\d, ]{5,8}(?= )",
                    @"(?<= PEAK Price \(EUR\/MWh\) \|\| [\d, -]+\n)[\d, ]{5,8}(?= )",
                    @"(?<= PEAK Price \(EUR\/MWh\) \|\| )[\d, ]{5,8}(?= )",
                ],
                [
                    @"(?<=OFFPEAK \(PLN\/MWh\) \|\| [\d, ]+ \|\| [\d, -]+\n)[\d, ]{6,8}(?=\n)",
                    @"(?<=OFFPEAK \(PLN\/MWh\) \|\| [\d, -]+\n)[\d, ]{6,8}(?= )",
                    @"(?<=OFFPEAK \(PLN\/MWh\) \|\| )[\d, ]{6,8}(?= )"
                ],
                [
                    @"(?<=OFFPEAK Price \(EUR\/MWh\) \|\| [\d, -]+ \|\| [\d-]+ \|\| [\d-]+\n)[\d, ]{5,8}(?= )",
                    @"(?<=OFFPEAK Price \(EUR\/MWh\) \|\| )[\d, ]{5,8}(?= )",

                ]
            ],
            [
                [
                    @"(?<=Wolumen BASE \|\| [\d  -]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen BASE\n[\d  -]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen BASE\n)[\d  ]{7,10}(?= )"
                ],
                [
                    @"(?<=Wolumen PEAK\n[\d  ]+\n[\d  -]+ \|\| [\d  -]+\n)[\d ]{7,10}(?=\n| )",
                    @"(?<=Wolumen PEAK\n[\d  ]+ \|\| [\d  -]+\n)[\d ]{7,10}(?=\n)",
                    @"(?<=Wolumen PEAK\n[\d -]+ \|\| [\d  ]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen PEAK\n[\d  ]+\n[\d  -]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen PEAK \|\| [\d  ]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen PEAK\n[\d  -]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen PEAK\n)[\d ]{7,10}(?= )"
                ],
                [
                    @"(?<=Wolumen OFFPEAK\n[\d  ]+\n[\d  -]+ \|\| [\d  -]+\n)[\d ]{7,10}(?=\n| )",
                    @"(?<=Wolumen OFFPEAK\n[\d  ]+ \|\| [\d  -]+\n)[\d ]{7,10}(?=\n)",
                    @"(?<=Wolumen OFFPEAK\n[\d -]+ \|\| [\d  ]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen OFFPEAK\n[\d  ]+\n[\d  -]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen OFFPEAK \|\| [\d  ]+\n)[\d ]{7,10}(?= )",
                    @"(?<=Wolumen OFFPEAK\n[\d  -]+\n)[\d ]{7,10}(?= )",
                ],
                [
                    @"(?<=Średni wolumen dzienny\n[\d -]+\n)[\d ]{6,9}(?= )",
                    @"(?<=Średni wolumen dzienny\n)[\d ]{6,9}(?= )",
                    @"(?<=Auction No\. 2\n[\d ]+ \|\| [\d -]+\n)[\d ]{6,9}(?=\n)",
                    @"(?<=Auction No\. 2\n[\d  -]+\n)[\d ]{6,9}(?= )",
                    @"(?<=Auction No\. 2\n)[\d ]{6,9}(?= )",
                ]
            ],
            [
                [
                    @" \|\| )-(?= \|\| - \|\| - \|\| 0( \|\| |\n))", //0
                    @"(?<=\n)[\d, ]{5,}(?= \|\| [\d ,-]{4,} \|\| [\d, ]{6,} \|\| [\d, -]{4,}\n", //1
                    @"(?<=\n)[\d, ]{5,}(?= \|\| [\d ,-]{4,} \|\| [\d, ]{6,} \|\| [\d, -]{4,} \|\| [\d  ]{3,}\n", //2
                    @"(?<= )[\d, ]{5,}(?= \|\| [\d, -]{4,}\n[\d]{1,2} \|\| [\d, ]{5,} \|\| [\d ]+ \|\| ", //3
                    @"(?<= )[\d, ]{5,}(?= \|\| [\d, -]{4,} \|\| [\d  ]{3,}\n[\d]{1,2} \|\| [\d, ]{5,} \|\| [\d ]+ \|\| ", //4
                    @"(?<=\n)[\d, ]{5,}(?= \|\| [\d, -]{4,} \|\| [\d ,]{5,} \|\| [\d, ]{5,} \|\| [\d, -]{4,} \|\| [\d ,]{4,}\n", //5
                    @"(?<= )[\d, ]{5,}(?= \|\| [\d, -]{4,} \|\| [\d ,]{4,}\n[\d]{1,2} \|\| [\d ]{2,} \|\| ", //6
                    @"(?<= )[\d, ]{5,}(?= \|\| [\d, -]{4,} \|\| [\d ,]{4,} \|\| [\d ]+\n[\d]{1,2} \|\| [\d ]{2,} \|\| ", //7
                    @" \|\| )[\d, ]{6,}(?= \|\| [\d, -]{4,} \|\| [\d,]{5,}(\n| \|\| |[\d ]+))", //8
                    @" \|\| )[\d, ]{6,}(?= \|\| - \|\| [\d,]{5,}(\n| \|\| |[\d ]+( \|\| |\n)))", //9
                    @" \|\| )[\d, ]{6,}(?= \|\| [\d, ]{4,} \|\| [\d ]+ \|\| [\d]{1,2} \|\| [\d,]{6,} \|\| [\d,]{5,} \|\| [\d ]+\n)", //10
                    @" \|\| )[\d, ]{6,}(?= \|\| [\d, ]{4,} \|\| [\d ]+ \|\| [\d]{1,2} \|\| [\d,]{6,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d ]{3,}\n)", //11
                    @" \|\| )[\d, ]{6,}(?= \|\| [\d, -]{4,} \|\| [\d ]{5,}\n)", //12
                    @" \|\| )[\d, ]{6,}(?= \|\| [\d, ]{4,} \|\| [\d ]+ \|\| [\d]{3,}\n)", //13
                    @" \|\| )[\d, ]{5,}(?= \|\| [\d, -]{4,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d]{2} \|\| [\d,]{5,} \|\| [\d, -]{4,} \|\| [\d,]{5,} \|\| [\d ]+\n)", //14
                    @" \|\| )[\d, ]{5,}(?= \|\| [\d, -]{4,} \|\| [\d,]{5,} \|\| [\d ]+\n)", //15
                    @"(?<= )[\d, ]{5,}(?=\n[\d]{1,2} \|\| [\d, -]{5,} \|\| [\d, ]{5,} \|\| [\d ]+ \|\| ", //16
                    @"(?<=\n)[\d,]{5,}(?= \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]{3,7} \|\| [\d  ]{3,}\n", //17
                    @"(?<=\n)[\d,]{5,}(?= \|\| [\d ,-]{4,} \|\| [\d,]{5,} \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d  ]{3,}\n", //18
                    @"(?<=\n)[\d,]{5,}(?= \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]{3,7}\n", //19
                    @"(?<= )[\d, ]{5,}(?= \|\| [\d, -]{4,} \|\| [\d, ]{5,} \|\| [\d ]+ \|\| [\d  ]+\n[\d]{1,2} \|\| ", //20
                    @"(?<= )[\d, ]{5,}(?= \|\| [\d,-]+ \|\| [\d,]{5,} \|\| [\d ]+\n[\d]{1,2} \|\| ", //21
                    @"(?<= )[\d, ]{5,}(?= \|\| [\d]{3,}\n[\d]{1,2} \|\| [\d, -]+ \|\| [\d,]{5,} \|\| [\d]+ \|\| ", //22
                    @"(?<=\n)[\d, ]{5,}(?= \|\| [\d, ]{5,} \|\| [\d]{3,}\n", //23
                    @"(?<=\n)[\d,]{5,}(?= \|\| [\d, ]{5,}\n", //24
                ],
                [
                    @" \|\| - \|\| - \|\| )-(?= \|\| 0( \|\| |\n))", //0
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?= \|\| [\d ]+ \|\| [\d  ]{3,}\n[\d]{1,2} \|\| ", //1
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?= \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,}(\n| \|\| [\d  ]{3,5}\n)", //2
                    @"(?<=\n[\d, ]{5,} \|\| [\d, -]{4,} \|\| )[\d ,]{5,}(?= \|\| [\d, ]{5,} \|\| [\d, -]{4,} \|\| [\d ,]{4,}\n", //3
                    @"(?<=\n[\d, ]{5,} \|\| [\d, -]{4,} \|\| [\d ,]{5,} \|\| [\d, ]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?=(\n| \|\| [\d  ]{3,5}\n)[\d]{1} \|\| [\d ]+ \|\| ", //4
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?= \|\| [\d ]{3,7} \|\| [\d  ]{3,}\n[\d]{1} \|\| ", //5
                    @" \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{4,}(?= \|\| [\d ]+((\n| \|\| [\d ]{3,5}| \|\| [\d-]{7} \|\| [\d-]{7})| \|\| [\d]{2} \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{4,} \|\| [\d ]+\n))", //6
                    @" \|\| [\d, ]{6,} \|\| - \|\| )[\d,]{5,}(?=(\n| \|\| |[\d ]+( \|\| |\n)))", //7
                    @" \|\| [\d, ]{6,} \|\| )[\d,]{5,}(?= \|\| [\d ]+((\n| \|\| [\d]{3,5}\n)| \|\| [\d]{1,2} \|\| [\d,]{6,} \|\| [\d,]{5,} \|\| [\d ]+(\n| \|\| [\d ]{3,5}\n)))", //8
                    @" \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?= \|\| [\d ]+((\n| \|\| [\d  ]{3,5})| \|\| [\d]{2} \|\| [\d,-]{5,} \|\| [\d,]{5,} \|\| [\d ]+(\n| \|\| [\d  ]{3,5})))", //9
                    @" \|\| )[\d,]{5,}(?= \|\| [\d ]+((\n| \|\| [\d  ]{3,5}\n)| \|\| [\d]{2} \|\| [\d,]{5,} \|\| [\d ]+(\n| \|\| [\d ]{3,5}\n)))", //10
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?= \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]{3,7}\n", //11
                    @"(?<= [\d, ]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?= \|\| [\d ]+\n[\d]{1,2} \|\| ", //12
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| )[\d,]{5,}(?= \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]{3,7} \|\| [\d  ]{3,}\n" //13
                ],
                [
                    @" \|\| - \|\| - \|\| - \|\| )0(?=( \|\| |\n))", //0
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| )[\d ]+(?= \|\| [\d  ]{3,}\n[\d]{1,2} \|\| ", //1
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]+ \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| )[\d ]{3,7}(?= \|\| [\d  ]{3,}\n[\d]{1} \|\| ", //2
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| )[\d ]+(?= \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]{3,7}\n", //3
                    @"(?<= [\d, ]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| )[\d ]+(?=\n[\d]{1,2} \|\| ", //4
                    @"(?<=\n[\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| )[\d ]+(?= \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| [\d ]{3,7} \|\| [\d  ]{3,}\n", //5
                    @" \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{4,} \|\| )[\d ]+(?=((\n| \|\| [\d ]{3,5}| \|\| [\d-]{7} \|\| [\d-]{7})| \|\| [\d]{2} \|\| [\d,]{5,} \|\| [\d,-]{4,} \|\| [\d,]{4,} \|\| [\d ]+\n))", //6
                    @" \|\| [\d, ]{6,} \|\| - \|\| [\d,]{5,} \|\| )[\d ]+(?=( \|\| |\n))", //7
                    @" \|\| [\d, ]{6,} \|\| [\d,]{5,} \|\| )[\d ]+(?=((\n| \|\| [\d]{3,5}\n)| \|\| [\d]{1,2} \|\| [\d,]{6,} \|\| [\d,]{5,} \|\| [\d ]+(\n| \|\| [\d ]{3,5}\n)))", //8
                    @" \|\| [\d,-]{4,} \|\| [\d,]{5,} \|\| )[\d ]+(?=((\n| \|\| [\d  ]{3,5})| \|\| [\d]{2} \|\| [\d,-]{5,} \|\| [\d,]{5,} \|\| [\d ]+(\n| \|\| [\d  ]{3,5})))", //9
                    @" \|\| [\d,]{5,} \|\| )[\d ]+(?=((\n| \|\| [\d  ]{3,5}\n)| \|\| [\d]{2} \|\| [\d,]{5,} \|\| [\d ]+(\n| \|\| [\d ]{3,5}\n)))", //10
                    @" \|\| )[\d ]{3,}(?=(\n| \|\| [\d]{3,5}\n)| \|\| [\d]{2} \|\| [\d ]+(\n| \|\| [\d]{3,5}\n))", //11
                ]
            ],
            [
                [
                    @"(?<=BASE_Y-)[\d]{2}",
                    @"(?<=PEAK5_Y-)[\d]{2}"
                ],
                [
                    @" \|\| )[\d,-]+"
                ],
                [
                    @" \|\| [\d,-]+ \|\| )[\d,-]+"
                ],
                [
                    @" \|\| [\d,-]+ \|\| [\d,-]+ \|\| [\d,-]+ \|\| )[\d,-]+"
                ],
                [
                    @" \|\| [\d,-]+ \|\| [\d,-]+ \|\| [\d,-]+ \|\| [\d,-]+ \|\| )[\d,-]+"
                ],
                [
                    @" \|\| [\d,-]+ \|\| [\d,-]+ \|\| [\d,-]+ \|\| [\d,-]+ \|\| [\d,-]+ \|\| )[\d ]+(?= )"
                ]
            ],
            [
                [
                    @"(?<=PMOZE_A)"
                ],
                [
                    @"(?<=Cena średnioważona \(PLN\/MWh\)\n[\d, -]+ \|\| [\d, -]+ \|\| [\d, -]+ \|\| )[\d, -]+(?= \|\| [\d, -]+ \|\| [\d, -]+\n)"
                ],
                [
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ]+ \|\| [\d ]+ \|\| [\d -]+ \|\| )[\d, ]+(?= \|\| [\d ]+ \|\| [\d -]+\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ,]+ \|\| [\d ,]+ \|\| [\d ,-]+ \|\| )[\d, ]+(?= \|\| [\d ]+ \|\| [\d -]+\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ]+ \|\| [\d -]+ \|\| [\d ]+ \|\| [\d -]+\n[\d ]+ \|\| )[\d ]+(?=\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ,]+ \|\| [\d ,-]+ \|\| [\d ]+ \|\| [\d -]+\n[\d, ]+ \|\| )[\d ]+(?=\n)",
                ]
            ],
            [
                [
                    @"(?<=PMOZE-BIO)"
                ],
                [
                    @"(?<=Cena średnioważona \(PLN\/MWh\)\n)[\d, ]+(?= \|\| [\d, ]+ \|\| [\d, -]+ \|\| [\d, -]+ \|\| [\d, -]+ \|\| [\d, -]+\n)",
                    @"(?<=Cena średnioważona \(PLN\/MWh\)\n[\d, ]+ \|\| [\d, -]+ \|\| [\d, -]+ \|\| [\d, -]+\n)[\d, ]+(?= \|\| [\d, -]+\n)",
                ],
                [
                    @"(?<=Wolumen miesięczny \(MWh\)\n)[\d, ]+(?= \|\| [\d ]+ \|\| [\d -]+ \|\| [\d ]+ \|\| [\d ]+ \|\| [\d -]+\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ]+ \|\| [\d -]+ \|\| [\d ]+ \|\| [\d -]+\n)[\d ]+(?= \|\| [\d ]+\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ]+ \|\| [\d ]+\n)[\d ]+(?= \|\| [\d -]+ \|\| [\d ]+ \|\| [\d -]+\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ,]+ \|\| [\d ,-]+ \|\| [\d ]+ \|\| [\d -]+\n)[\d ]+(?= \|\| [\d, ]+\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n)[\d, ]+(?= \|\| [\d ]+ \|\| [\d -]+ \|\| [\d ,]+ \|\| [\d ,]+ \|\| [\d ,-]+\n)",
                    @"(?<=Wolumen miesięczny \(MWh\)\n[\d ]+ \|\| [\d ,]+\n)[\d ]+(?= \|\| [\d -]+ \|\| [\d ,]+ \|\| [\d ,-]+\n)",
                ]
            ],
            [
                [
                    @"(?<=PMEF_F)"
                ],
                [
                    @"(?<=Cena średnioważona \(PLN\/toe\)\n)[\d, ]+(?= \|\| [\d, ]+ \|\| [\d, -]+ \|\| [\d, -]+ \|\| [\d, -]+ \|\| [\d, -]+\n)",
                    @"(?<=Cena średnioważona \(PLN\/toe\)\n[\d, -]+\n)[\d, ]+(?= \|\| [\d, ]+ \|\| [\d, -]+ \|\| [\d, -]+ \|\| [\d, -]+\n)",
                ],
                [
                    @"(?<=Wolumen miesięczny \(toe\)\n)[\d, ]+(?= \|\| [\d ]+ \|\| [\d -]+ \|\| [\d ]+ \|\| [\d ]+ \|\| [\d -]+\n)",
                    @"(?<=Wolumen miesięczny \(toe\)\n[\d ]+ \|\| [\d -]+ \|\| [\d ]+ \|\| [\d -]+\n)[\d ]+(?= \|\| [\d ]+\n)",
                    @"(?<=Wolumen miesięczny \(toe\)\n[\d ]+ \|\| [\d ]+\n)[\d ]+(?= \|\| [\d -]+ \|\| [\d ]+ \|\| [\d -]+\n)",
                    @"(?<=Wolumen miesięczny \(toe\)\n[\d ,]+ \|\| [\d ,-]+ \|\| [\d ]+ \|\| [\d -]+\n)[\d ]+(?= \|\| [\d, ]+\n)",
                    @"(?<=Wolumen miesięczny \(toe\)\n)[\d, ]+(?= \|\| [\d ]+ \|\| [\d -]+ \|\| [\d ,]+ \|\| [\d ,]+ \|\| [\d ,-]+\n)",
                    @"(?<=Wolumen miesięczny \(toe\)\n[\d ]+ \|\| [\d ,]+\n)[\d ]+(?= \|\| [\d -]+ \|\| [\d ,]+ \|\| [\d ,-]+\n)",
                ]
            ],
            [
                [
                    @"(?<=Bilans praw majątkowych)"
                ],
                [
                    @"(?<=PMOZE_A(.*\n){4,5}Wystawione \|\| Wystawione\n[\d ]+ \|\| [\d ]+ \|\| )[\d ]+ \|\| [\d ]+(?=\n)",
                ],
                [
                    @"(?<=PMOZE_A(.*\n){7,8}Umorzone \|\| Umorzone\n[\d ]+ \|\| [\d ]+ \|\| )[\d ]+ \|\| [\d ]+(?=\n)",
                ],
                [
                    @"(?<=PMOZE_A(.*\n){10,11}Bilans \|\| Bilans\n[\d -]+ \|\| [\d -]+ \|\| )[\d -]+ \|\| [\d -]+(?=\n)",
                ],
                [
                    @"(?<=PMOZE_A(.*\n){13,15}Zablokowane do umorzenia \|\| Zablokowane do umorzenia\n[\d -]+ \|\| [\d -]+ \|\| )[\d -]+ \|\| [\d -]+(?=\n)",
                    @"(?<=PMOZE_A(.*\n){13}Zablokowane do umorzenia \|\| Zablokowane do umorzenia\n[\d -]+ \|\| [\d -]+\n[\d -]+ \|\| )[\d -]+(?=\n)",
                ],
            ],
            [
                [
                    @"(?<=PMOZE-BIO(.*\n){4,5}Wystawione \|\| Wystawione\n)[\d ]+ \|\| [\d ]+(?= \|\| [\d ]+ \|\| [\d ]+\n)",
                    @"(?<=PMOZE-BIO(.*\n){4,5}Wystawione \|\| Wystawione\n[\d ]+ \|\| [\d ]+\n)[\d ]+(?= \|\| [\d ]+\n)"
                ],
                [
                    @"(?<=PMOZE-BIO(.*\n){7,8}Umorzone \|\| Umorzone\n)[\d ]+ \|\| [\d ]+(?= \|\| [\d ]+ \|\| [\d ]+\n)",
                ],
                [
                    @"(?<=PMOZE-BIO(.*\n){10,11}Bilans \|\| Bilans\n)[\d -]+ \|\| [\d -]+(?= \|\| [\d -]+ \|\| [\d -]+\n)",
                ],
                [
                    @"(?<=PMOZE-BIO(.*\n){13,15}Zablokowane do umorzenia \|\| Zablokowane do umorzenia\n)[\d -]+ \|\| [\d -]+(?= \|\| [\d -]+ \|\| [\d -]+\n)",
                ],
            ],
            [
                [
                    @"(?<=PMEF_F(.*\n){4,5}Wystawione \|\| Wystawione\n)[\d ]+(?= \|\| [\d ]+ \|\| [\d ]+ \|\| [\d ]+\n)",
                ],
                [
                    @"(?<=PMEF_F(.*\n){7,8}Umorzone \|\| Umorzone\n)[\d ]+(?= \|\| [\d ]+ \|\| [\d ]+ \|\| [\d ]+\n)",
                    @"(?<=PMEF_F(.*\n){7,8}Umorzone \|\| Umorzone\n[\d ]+ \|\| [\d ]+\n)[\d ]+(?= \|\| [\d ]+\n)"
                ],
                [
                    @"(?<=PMEF_F(.*\n){10,12}Bilans \|\| Bilans\n)[\d -]+(?= \|\| [\d -]+ \|\| [\d -]+ \|\| [\d -]+\n)",
                ],
                [
                    @"(?<=PMEF_F(.*\n){13,15}Zablokowane do umorzenia \|\| Zablokowane do umorzenia\n)[\d -]+(?= \|\| [\d -]+ \|\| [\d -]+ \|\| [\d -]+\n)",
                ],
            ],
            [
                [
                    @"(?<=PMOZE_A(.*\n){13}Zablokowane do umorzenia \|\| Zablokowane do umorzenia\n[\d ]+ \|\| )[\d ]+(?=\n)",
                    @"(?<=PMOZE-BIO(.*\n){4,5}Wystawione \|\| Wystawione\n)[\d ]+(?= \|\| [\d ]+\n[\d ]+ \|\| [\d ]+\n)"
                ]
            ]
        };
        public PdfOpener()
        {

        }
        private void WriteList(List<string> list) {
            int i = 1;
            foreach (string s in list)
            {
                Debug.WriteLine(i.ToString() + ": " + s);
                i++;
            }
        }
        public Dictionary<string, List<string>> GetDATA()
        {
            return DATA;
        }
        private List<string> CloneList(List<string> l, int start, int end)
        {
            List<string> list = new List<string>();
            for (int i = start; i < end + 1; i++)
            {
                list.Add(l[i]);
            }
            return list;
        }
        public void CleanUp()
        {
            DATA.Clear();
            date.Clear();
            RDNmonthly.Clear();
            RDNvolume.Clear();
            RDNhours.Clear();
            Contracts.Clear();
            Peaks.Clear();
            PMOZE_A.Clear();
            PMOZE_BIO.Clear();
            PMEF_F.Clear();
            PMOZE_AcontractsBil.Clear();
            PMOZE_BIOcontractsBil.Clear();
            PMEF_FcontractsBil.Clear();
        }
        private void FormatData()
        {
            DATA.Add("Date", date);
            DATA.Add("BASE", CloneList(RDNmonthly, 0, 1));
            DATA.Add("PEAK", CloneList(RDNmonthly, 2, 3));
            DATA.Add("OFFPEAK", CloneList(RDNmonthly, 4, 5));
            RDNmonthly.Clear();
            DATA.Add("Volume", RDNvolume);
            List<string> tmp = new List<string>();
            for (int i = 1; i <= 24; i++)
            {
                tmp = RDNhours[i - 1].Trim().Split(" || ").ToList();
                for (int j = 0; j < tmp.Count; j++)
                {
                    if (tmp[j] == "-")
                    {
                        tmp[j] = "0";
                    }
                }
                DATA.Add("Hour" + i.ToString(), CloneList(tmp, 0, 2));
                tmp.Clear();
            }
            RDNhours.Clear();
            foreach (string s in Contracts)
            {
                tmp = s.Split(" || ").ToList();
                DATA.Add("BASE_Y-" + tmp[0], CloneList(tmp, 1, 5));
                tmp.Clear();
            }
            Contracts.Clear();
            foreach (string s in Peaks)
            {
                tmp = s.Split(" || ").ToList();
                DATA.Add("PEAK5_Y-" + tmp[0], CloneList(tmp, 1, 5));
                tmp.Clear();
            }
            Peaks.Clear();
            DATA.Add("PMOZE_A", PMOZE_A);
            DATA.Add("PMOZE_BIO", PMOZE_BIO);
            DATA.Add("PMEF_F", PMEF_F);
            string charset = "WUBZ";
            for (int i = 0; i < PMOZE_AcontractsBil.Count; i++)
            {
                tmp = PMOZE_AcontractsBil[i].Split(" || ").ToList();
                DATA.Add("PMOZE_A_" + charset[i], CloneList(tmp, 0, 1));
                tmp.Clear();
            }
            for (int i = 0; i < PMOZE_BIOcontractsBil.Count; i++)
            {
                tmp = PMOZE_BIOcontractsBil[i].Split(" || ").ToList();
                DATA.Add("PMOZE_BIO_" + charset[i], CloneList(tmp, 0, 1));
                tmp.Clear();
            }
            for (int i = 0; i < PMEF_FcontractsBil.Count; i++)
            {
                tmp.Add(PMEF_FcontractsBil[i]);
                DATA.Add("PMEF_F_" + charset[i], CloneList(tmp, 0, 0));
                tmp.Clear();
            }
        }
        private void SetMisc(string pageText)
        {
            string pattern = @"(?<=Exchange Rate \|\| )[\d,]+(?=(\r\n|\r|\n))";
            Match match = Regex.Match(pageText, pattern, RegexOptions.IgnoreCase);
            string exchangeRate = (match.Success) ? match.Value : "Error";
            List<string> tmp = [exchangeRate];
            DATA.Add("Exchange", tmp);

            pattern = @"[\d-]{7}(?= \|\| [\d-])";
            match = Regex.Match(pageText, pattern, RegexOptions.IgnoreCase);
            string MY = (match.Success) ? match.Value : "Error";
            date = MY.Split('-').ToList();
            date[0] = date[0].Replace("0", "");
            int month = 0;
            if (int.TryParse(date[0], out month))
            {
                CultureInfo polishCulture = new CultureInfo("pl-PL");
                date[0] = polishCulture.DateTimeFormat.GetMonthName(month);
            }
        }
        private string SetData(string pageText, string[][] pattern, List<string> list, bool additionalCheck)
        {
            bool found;
            int index = 0;
            foreach (string[] item in pattern)
            {
                found = false;
                foreach (string tryPattern in item)
                {
                    Match match = Regex.Match(pageText, tryPattern, RegexOptions.IgnoreCase);
                    if (match.Success)
                    {
                        if (match.Value != "")
                        {
                            list.Add(match.Value);
                            if (additionalCheck && !match.Value.Contains(" || "))
                            {
                                Match match2 = Regex.Match(pageText, Patterns[10][0][tryPattern.Contains("PMOZE_A") ? 0 : 1], RegexOptions.IgnoreCase);
                                if (match2.Success)
                                {
                                    list[tryPattern.Contains("PMOZE_A") ? 3 : 0] += " || " + match2.Value;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    Debug.WriteLine("PROBLEM WITH REGEX: " + index);
                    Debug.WriteLine(pageText);
                    return "Error";
                }
                index++;
            }
            return "Success";
        }
        private string SetRDNHours(string pageText, string[][] pattern, List<string> list)
        {
            bool found;
            int regexIndex;
            int dataIndex;
            CultureInfo culture = new CultureInfo("pl-PL");
            found = false;
            dataIndex = 0;
            foreach (string[] item in pattern)
            {
                for (int i = 1; i <= 24; i++)
                {
                    found = false;
                    regexIndex = 0;
                    foreach (string tryPattern in item)
                    {
                        Match match = Regex.Match(pageText, (regexIndex != 0 && (regexIndex < (dataIndex == 0 ? 8 : 6) || regexIndex > (dataIndex == 0 ? 15 : ((dataIndex == 2) ? 11 : 10)))) ? tryPattern + i.ToString() + @"(\n| \|))" : @"(?<=(\n| )" + i.ToString() + tryPattern, RegexOptions.IgnoreCase);
                        if (match.Success)
                        {
                            if (dataIndex == 0 && tryPattern == item[10])
                            {
                                Match match2 = Regex.Match(pageText, item[24] + i.ToString() + @"(\n| \|))", RegexOptions.IgnoreCase);
                                if (match2.Success)
                                {
                                    if (float.Parse(match.Value, culture) > float.Parse(match2.Value, culture))
                                        list.Add(match.Value);
                                    else
                                        list.Add(match2.Value);
                                }
                                else
                                {
                                    match2 = Regex.Match(pageText, item[23] + i.ToString() + @"(\n| \|))", RegexOptions.IgnoreCase);
                                    if (match2.Success)
                                    {
                                        if (float.Parse(match.Value, culture) > float.Parse(match2.Value, culture))
                                            list.Add(match.Value);
                                        else
                                            list.Add(match2.Value);
                                    }
                                    else
                                        list.Add(match.Value);
                                }
                            }
                            else if (dataIndex == 0 && tryPattern == item[12])
                            {
                                Match match2 = Regex.Match(pageText, item[16] + i.ToString() + @"(\n| \|))", RegexOptions.IgnoreCase);
                                if (match2.Success)
                                {
                                    if (float.Parse(match.Value, culture) > float.Parse(match2.Value, culture))
                                        list.Add(match.Value);
                                    else
                                        list.Add(match2.Value);
                                }
                                else
                                {
                                    match2 = Regex.Match(pageText, item[22] + i.ToString() + @"(\n| \|))", RegexOptions.IgnoreCase);
                                    if (match2.Success)
                                    {
                                        if (float.Parse(match.Value, culture) > float.Parse(match2.Value, culture))
                                            list.Add(match.Value);
                                        else
                                            list.Add(match2.Value);
                                    }
                                    else
                                        list.Add(match.Value);
                                }
                            }
                            else
                            {
                                if (dataIndex != 0)
                                    list[i - 1] = list[i - 1] + " || " + match.Value;
                                else
                                    list.Add(match.Value);
                            }
                            found = true;
                            break;
                        }
                        regexIndex++;
                    }
                    if (!found)
                    {
                        Debug.WriteLine("PROBLEM WITH REGEX: " + i.ToString());
                        Debug.WriteLine(pageText);
                        return "Error";
                    }
                }
                dataIndex++;
            }
            return "Success";
        }
        private string SetY(string pageText, string[][] pattern, List<string> list, string type)
        {
            MatchCollection matches = Regex.Matches(pageText, (type == "BASE_Y-")? pattern[0][0] : pattern[0][1], RegexOptions.IgnoreCase);
            if (matches.Count == 0)
            {
                Debug.WriteLine("PROBLEM WITH REGEX BASES");
                Debug.WriteLine(pageText);
                return "Error";
            }
            foreach (Match m in matches)
                list.Add(m.Value);
            int index = 0;
            int data;
            bool found;
            foreach (string[] item in pattern)
            {
                data = 0;
                if (index == 0)
                {
                    index++;
                    continue;
                }
                foreach(Match m in matches)
                {
                    found = false;
                    foreach (string tryPattern in item)
                    {
                        Match match = Regex.Match(pageText, "(?<=" + type + m.Value + tryPattern, RegexOptions.IgnoreCase);
                        if (match.Success)
                        {
                            list[data] += @" || " + ((match.Value == "-")? "0" : match.Value);
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        Debug.WriteLine("PROBLEM WITH REGEX: " + index);
                        Debug.WriteLine(pageText);
                        return "Error";
                    }
                    data++;
                }
                index++;
            }
            return "Success";
        }
        public string LoadFile(string pdfSource)
        {
            string previousPageText = "";
            string pageText;
            using (PdfReader reader = new PdfReader(pdfSource))
            {
                using (PdfDocument pdfDocument = new PdfDocument(reader))
                {
                    for (int page = 1; page <= pdfDocument.GetNumberOfPages(); page++)
                    {
                        var strat = new SeparatorStrategy();
                        pageText = PdfTextExtractor.GetTextFromPage(pdfDocument.GetPage(page), strat);
                        switch (page)
                        {
                            case 1:
                                SetMisc(pageText);
                                if (date[0] == "Error" || SetData(pageText, Patterns[0], RDNmonthly, false) == "Error")
                                    return "Problem z wczytaniem pliku .PDF!";
                                break;
                            case 2:
                                if (SetData(pageText, Patterns[1], RDNvolume, false) == "Error")
                                    return "Problem z wczytaniem pliku .PDF!";
                                break;
                            case 3:
                                if (SetRDNHours(pageText, Patterns[2], RDNhours) == "Error")
                                    return "Problem z wczytaniem pliku .PDF!";
                                break;
                            case 4:
                                if (SetY(pageText, Patterns[3], Contracts, "BASE_Y-") == "Error")
                                    return "Problem z wczytaniem pliku .PDF!";
                                break;
                            case 5:
                                if (SetY(pageText, Patterns[3], Peaks, "PEAK5_Y-") == "Error")
                                    return "Problem z wczytaniem pliku .PDF!";
                                break;
                            case 7:
                                previousPageText = pageText;
                                break;
                            case 8:
                                Match match = Regex.Match(previousPageText, Patterns[4][0][0], RegexOptions.IgnoreCase);
                                if (match.Success)
                                {
                                    if (SetData(previousPageText, Patterns[4], PMOZE_A, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                else
                                {
                                    if (SetData(pageText, Patterns[4], PMOZE_A, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                previousPageText = pageText;
                                break;
                            case 9:
                                match = Regex.Match(previousPageText, Patterns[5][0][0], RegexOptions.IgnoreCase);
                                if (match.Success)
                                {
                                    if (SetData(previousPageText, Patterns[5], PMOZE_BIO, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                else
                                {
                                    if (SetData(pageText, Patterns[5], PMOZE_BIO, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                previousPageText = pageText;
                                break;
                            case 10:
                                match = Regex.Match(previousPageText, Patterns[6][0][0], RegexOptions.IgnoreCase);
                                if (match.Success)
                                {
                                    if (SetData(previousPageText, Patterns[6], PMEF_F, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                else
                                {
                                    if (SetData(pageText, Patterns[6], PMEF_F, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                break;
                            case 11:
                                previousPageText = pageText;
                                break;
                            case 12:
                                match = Regex.Match(previousPageText, Patterns[7][0][0], RegexOptions.IgnoreCase);
                                if (match.Success)
                                {
                                    if (SetData(previousPageText, Patterns[7], PMOZE_AcontractsBil, true) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                    if (SetData(previousPageText, Patterns[8], PMOZE_BIOcontractsBil, true) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                    if (SetData(previousPageText, Patterns[9], PMEF_FcontractsBil, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                else
                                {
                                    if (SetData(pageText, Patterns[7], PMOZE_AcontractsBil, true) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                    if (SetData(pageText, Patterns[8], PMOZE_BIOcontractsBil, true) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                    if (SetData(pageText, Patterns[9], PMEF_FcontractsBil, false) == "Error")
                                        return "Problem z wczytaniem pliku .PDF!";
                                }
                                break;
                        }
                    }
                }
            }
            FormatData();
            return "Wczytano .PDF pomyślnie!";
        }
    }
}
