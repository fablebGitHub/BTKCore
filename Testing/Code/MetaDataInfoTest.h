#ifndef MetaDataInfoTest_h
#define MetaDataInfoTest_h

#include <btkMetaDataInfo.h>
#include <btkConvert.h>

CXXTEST_SUITE(MetaDataInfoTest)
{
  CXXTEST_TEST(ConstructorInt8)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((int8_t)5);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Byte);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 0);
    TS_ASSERT_EQUALS(*static_cast<int8_t*>(test->GetValues()[0]), 5);
  };
  
  CXXTEST_TEST(ConstructorInt16)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((int16_t)5);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Integer);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 0);
    TS_ASSERT_EQUALS(*static_cast<int16_t*>(test->GetValues()[0]), 5);
  };
  
  CXXTEST_TEST(ConstructorFloat)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((float)5.0);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Real);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 0);
    TS_ASSERT_DELTA(*static_cast<float*>(test->GetValues()[0]), 5.0, 0.00001);
  };
  
  CXXTEST_TEST(ConstructorChar)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New("test");
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 1);
    TS_ASSERT_EQUALS(test->GetDimensions()[0], 4);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[0]), "test");
  };
  
  CXXTEST_TEST(ConstructorVectorInt8)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 2);
    std::vector<int8_t> val = std::vector<int8_t>(4, 55);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Byte);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    for (int i = 0 ; i < 4 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<int8_t*>(test->GetValues()[i]), 55);
  };
  
  CXXTEST_TEST(ConstructorVectorInt16)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 3);
    std::vector<int16_t> val = std::vector<int16_t>(4, 655);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Integer);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    for (int i = 0 ; i < 4 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<int16_t*>(test->GetValues()[i]), 655);
    TS_ASSERT_EQUALS(*static_cast<int16_t*>(test->GetValues()[4]), 0);
    TS_ASSERT_EQUALS(*static_cast<int16_t*>(test->GetValues()[5]), 0);
  };
  
  CXXTEST_TEST(ConstructorVectorFloat)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 3);
    std::vector<float> val = std::vector<float>(4, (float)273.45);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Real);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    for (int i = 0 ; i < 4 ; ++i)
      TS_ASSERT_DELTA(*static_cast<float*>(test->GetValues()[i]), 273.45, 0.0001);
    TS_ASSERT_DELTA(*static_cast<float*>(test->GetValues()[4]), 0.0, 0.00001);
    TS_ASSERT_DELTA(*static_cast<float*>(test->GetValues()[5]), 0.0, 0.00001);    
  };
  
  CXXTEST_TEST(ConstructorVectorCharNormal)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(4, 4);
    std::vector<std::string> val = std::vector<std::string>(4, "test");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 4);
    for (int i = 0 ; i < 4 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[i]), "test");
  };
  
  CXXTEST_TEST(ConstructorVectorCharResizeEmptyDim1)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(0);
    std::vector<std::string> val = std::vector<std::string>(0);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 0);
    TS_ASSERT_EQUALS(test->GetValues().size(), 1);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[0]), " ");

  };
  
  CXXTEST_TEST(ConstructorVectorCharResizeLowerDim1)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(0);
    std::vector<std::string> val = std::vector<std::string>(4, "test");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 0);
    TS_ASSERT_EQUALS(test->GetValues().size(), 1);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[0]), "t");
  };
  
  CXXTEST_TEST(ConstructorVectorCharResizeUpperDim1)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(1, 5);
    std::vector<std::string> val = std::vector<std::string>(4, "test");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 1);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[0]), "test ");
  };
  
  CXXTEST_TEST(ConstructorVectorCharResizeEmptyDim2)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2,5);
    std::vector<std::string> val = std::vector<std::string>(0);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[i]), "     ");
  };
  
  CXXTEST_TEST(ConstructorVectorCharResizeLowerDim2)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 2);
    std::vector<std::string> val = std::vector<std::string>(4, "test");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 2);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[0]), "te");
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[1]), "te");
  };
  
  CXXTEST_TEST(ConstructorVectorCharResizeUpperDim2)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 5);
    std::vector<std::string> val = std::vector<std::string>(4, "test");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 5);
    for (int i = 0 ; i < 4 ; ++i)
    {
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[i]), "test ");
    }
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValues()[4]), "     ");

  };
  
  CXXTEST_TEST(ConstructorVectorCharPointLabels)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 0); dim[0] = 32;
    std::vector<std::string> val = std::vector<std::string>(0);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 0);
  };

  CXXTEST_TEST(SetValuesFromVectorString)
  {
    std::vector<std::string> val = std::vector<std::string>(0);
    val.push_back("NAME");
    val.push_back("CALIBRATION");
    val.push_back("FULL_DESCRIPTION");
    val.push_back("SETUP");
    val.push_back("DATE");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetDimension(0), 16);
    TS_ASSERT_EQUALS(test->GetDimension(1), 5);
    TS_ASSERT_EQUALS(test->GetValues().size(), 5);
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(0)), "NAME            ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(1)), "CALIBRATION     ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(2)), "FULL_DESCRIPTION");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(3)), "SETUP           ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(4)), "DATE            ");
  };

  CXXTEST_TEST(SetValueFromString)
  {
    std::vector<std::string> val = std::vector<std::string>(0);
    val.push_back("NAME");
    val.push_back("CALIBRATION");
    val.push_back("FULL_DESCRIPTION");
    val.push_back("SETUP");
    val.push_back("DATE");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(val);
    test->SetValue(2,"SHORTER");
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetDimension(0), 16);
    TS_ASSERT_EQUALS(test->GetDimension(1), 5);
    TS_ASSERT_EQUALS(test->GetValues().size(), 5);
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(0)), "NAME            ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(1)), "CALIBRATION     ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(2)), "SHORTER         ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(3)), "SETUP           ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(4)), "DATE            ");
    test->SetValue(2,"BIGGERANDBIGGERANDBIGGER");
    TS_ASSERT_EQUALS(test->GetDimension(0), 24);
    TS_ASSERT_EQUALS(test->GetDimension(1), 5);
    TS_ASSERT_EQUALS(test->GetValues().size(), 5);
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(0)), "NAME                    ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(1)), "CALIBRATION             ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(2)), "BIGGERANDBIGGERANDBIGGER");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(3)), "SETUP                   ");
    TS_ASSERT_EQUALS(*static_cast<const std::string*>(test->GetValue(4)), "DATE                    ");
  };
  
  CXXTEST_TEST(SetFormatChar2Integer)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 5);
    std::vector<std::string> val = std::vector<std::string>(4, "test");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    test->SetFormat(btk::MetaDataInfo::Integer);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Integer);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 25);
    for (int i = 0 ; i < 25 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<int16_t*>(test->GetValue(i)), 0);
  };
  
  CXXTEST_TEST(SetFormatFloat2Integer)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 5);
    std::vector<float> val = std::vector<float>(25, (float)1.950);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Real);
    test->SetFormat(btk::MetaDataInfo::Integer);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Integer);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 25);
    for (int i = 0 ; i < 25 ; ++i)
    {
      TS_ASSERT_EQUALS(*static_cast<int16_t*>(test->GetValue(i)), 0);
    }
  };
  
  CXXTEST_TEST(SetFormatFloat2CharDim1)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(0);
    std::vector<float> val = std::vector<float>(1, (float)1.950);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Real);
    test->SetFormat(btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 0);
    TS_ASSERT_EQUALS(test->GetValues().size(), 1);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValue(0)), " ");
  };

  CXXTEST_TEST(SetFormatFloat2CharDim2)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 5);
    std::vector<float> val = std::vector<float>(25, (float)1.950);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Real);
    test->SetFormat(btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Char);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValue(i)), "     ");
  };
  
  CXXTEST_TEST(SetDimensionForFloat)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 5);
    std::vector<float> val = std::vector<float>(25, (float)1.950);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    test->SetDimension(0, 6);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 30);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<float*>(test->GetValue(i*6+5)), 0.0);
    test->SetDimension(1, 6);
    TS_ASSERT_EQUALS(test->GetValues().size(), 36);
    for (int i = 30 ; i < 35 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<float*>(test->GetValue(i)), 0.0);
  };
  
  CXXTEST_TEST(SetDimensionForChar)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(2, 5);
    std::vector<std::string> val = std::vector<std::string>(5, "test ");
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    test->SetDimension(0, 2);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 2);
    TS_ASSERT_EQUALS(test->GetValues().size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValue(i)), "te");
  };
  
  CXXTEST_TEST(ResizeDimensionsFrom0To1Byte)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((int8_t)0);
    test->ResizeDimensions(1);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 1);
    TS_ASSERT_EQUALS(test->GetValues().size(), 1);
  };
  
  CXXTEST_TEST(ResizeDimensionsFrom3To1Float)
  {
    std::vector<uint8_t> dim = std::vector<uint8_t>(3, 3);
    std::vector<float> val = std::vector<float>(27, (float)1.950);
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(dim, val);
    test->ResizeDimensions(1);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 1);
    TS_ASSERT_EQUALS(test->GetValues().size(), 3);
  };
  
  CXXTEST_TEST(ResizeDimensionsFrom1To0Char)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New("test");
    test->ResizeDimensions(0);
    TS_ASSERT_EQUALS(test->GetDimensions().size(), 0);
    TS_ASSERT_EQUALS(test->GetValues().size(), 1);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test->GetValue(0)), "t");

  };
  
  CXXTEST_TEST(Clone)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((float)1.435);
    btk::MetaDataInfo::Pointer test2 = test->Clone();
    test2->SetValues("test");
    TS_ASSERT_DELTA(*static_cast<float*>(test->GetValue(0)),1.435, 0.0001);
    TS_ASSERT_EQUALS(test->GetFormat(), btk::MetaDataInfo::Real);
    TS_ASSERT_EQUALS(*static_cast<std::string*>(test2->GetValue(0)), "test");
    TS_ASSERT_EQUALS(test2->GetFormat(), btk::MetaDataInfo::Char);
  };

  CXXTEST_TEST(String2String)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<std::string>(5, "test"));
    std::vector<std::string> val = test->ToString();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), "test");
  };

  CXXTEST_TEST(Byte2String)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((int8_t)5);
    std::vector<std::string> val = test->ToString();
    TS_ASSERT_EQUALS(val.size(), 1);
    TS_ASSERT_EQUALS(val.at(0), "\x05");
  };

  CXXTEST_TEST(Integer2String)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<int16_t>(5, 379));
    std::vector<std::string> val = test->ToString();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), "379");
  };

  CXXTEST_TEST(Real2String)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<float>(5, 0.83333f));
    std::vector<std::string> val = test->ToString();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), "0.83333");
  };

  CXXTEST_TEST(String2Byte)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<std::string>(5, "test"));
    std::vector<int8_t> val = test->ToInt8();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 0);
  };

  CXXTEST_TEST(Byte2Byte)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((int8_t)5);
    std::vector<int8_t> val = test->ToInt8();
    TS_ASSERT_EQUALS(val.size(), 1);
    TS_ASSERT_EQUALS(val.at(0), 5);
  };

  CXXTEST_TEST(Integer2Byte)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<int16_t>(5, 379));
    std::vector<int8_t> val = test->ToInt8();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 123);
  };

  CXXTEST_TEST(Real2Byte)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<float>(5, 0.1f));
    std::vector<int8_t> val = test->ToInt8();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 0);
  };

  CXXTEST_TEST(String2Integer)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<std::string>(5, "test"));
    std::vector<int16_t> val = test->ToInt16();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 0);
  };

  CXXTEST_TEST(Byte2Integer)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((int8_t)5);
    std::vector<int16_t> val = test->ToInt16();
    TS_ASSERT_EQUALS(val.size(), 1);
    TS_ASSERT_EQUALS(val.at(0), 5);
  };

  CXXTEST_TEST(Integer2Integer)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<int16_t>(5, 379));
    std::vector<int16_t> val = test->ToInt16();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 379);
  };

  CXXTEST_TEST(Real2Integer)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<float>(5, 0.1f));
    std::vector<int16_t> val = test->ToInt16();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 0);
  };

  CXXTEST_TEST(String2Real)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<std::string>(5, "test"));
    std::vector<float> val = test->ToFloat();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_DELTA(val.at(i), 0, 0.0001);
  };

  CXXTEST_TEST(Byte2Real)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New((int8_t)5);
    std::vector<float> val = test->ToFloat();
    TS_ASSERT_EQUALS(val.size(), 1);
    TS_ASSERT_DELTA(val.at(0), 5, 0.0001);
  };

  CXXTEST_TEST(Integer2Real)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<int16_t>(5, 379));
    std::vector<float> val = test->ToFloat();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_DELTA(val.at(i), 379, 0.0001);
  };

  CXXTEST_TEST(Real2Real)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<float>(5, 0.1f));
    std::vector<float> val = test->ToFloat();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_DELTA(val.at(i), 0.1, 0.0001);
  };

  CXXTEST_TEST(Float2Double)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<float>(5, 0.1f));
    std::vector<double> val = test->ToDouble();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_DELTA(val.at(i), 0.1, 0.0001);
  };

  CXXTEST_TEST(Int82Int)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<int8_t>(5, 45));
    std::vector<int> val = test->ToInt();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 45);
  };

  CXXTEST_TEST(Int162Double)
  {
    btk::MetaDataInfo::Pointer test = btk::MetaDataInfo::New(std::vector<int16_t>(5, 369));
    std::vector<double> val = test->ToDouble();
    TS_ASSERT_EQUALS(val.size(), 5);
    for (int i = 0 ; i < 5 ; ++i)
      TS_ASSERT_EQUALS(val.at(i), 369);
  };

};

CXXTEST_SUITE_REGISTRATION(MetaDataInfoTest)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorInt8)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorInt16)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorFloat)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorChar)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorInt8)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorInt16)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorFloat)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharNormal)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharResizeEmptyDim1)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharResizeLowerDim1)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharResizeUpperDim1)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharResizeEmptyDim2)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharResizeLowerDim2)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharResizeUpperDim2)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ConstructorVectorCharPointLabels)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, SetValuesFromVectorString)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, SetValueFromString)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, SetFormatChar2Integer)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, SetFormatFloat2Integer)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, SetFormatFloat2CharDim1)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, SetFormatFloat2CharDim2)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, SetDimensionForFloat)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ResizeDimensionsFrom0To1Byte)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ResizeDimensionsFrom3To1Float)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, ResizeDimensionsFrom1To0Char)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Clone)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, String2String)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Byte2String)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Integer2String)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Real2String)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, String2Byte)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Byte2Byte)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Integer2Byte)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Real2Byte)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, String2Integer)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Byte2Integer)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Integer2Integer)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Real2Integer)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, String2Real)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Byte2Real)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Integer2Real)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Real2Real)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Float2Double)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Int82Int)
CXXTEST_TEST_REGISTRATION(MetaDataInfoTest, Int162Double)  

#endif
