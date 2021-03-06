#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "settings/lib/ISettingCallback.h"

#include <map>
#include <string>
#include <vector>

#ifdef TARGET_WINDOWS
#ifdef GetDateFormat
#undef GetDateFormat
#endif // GetDateFormat
#ifdef GetTimeFormat
#undef GetTimeFormat
#endif // GetTimeFormat
#endif // TARGET_WINDOWS

class TiXmlNode;

class CLangInfo : public ISettingCallback
{
public:
  CLangInfo();
  virtual ~CLangInfo();

  virtual void OnSettingChanged(const CSetting *setting);

  bool Load(const std::string& strFileName, bool onlyCheckLanguage = false);

  std::string GetGuiCharSet() const;
  std::string GetSubtitleCharSet() const;

  // three char language code (not win32 specific)
  const std::string& GetLanguageCode() const { return m_languageCodeGeneral; }

  bool SetLanguage(const std::string &strLanguage);
  bool CheckLoadLanguage(const std::string &language);

  const std::string& GetAudioLanguage() const;
  // language can either be a two char language code as defined in ISO639
  // or a three char language code
  // or a language name in english (as used by XBMC)
  void SetAudioLanguage(const std::string& language);
  
  // three char language code (not win32 specific)
  const std::string& GetSubtitleLanguage() const;
  // language can either be a two char language code as defined in ISO639
  // or a three char language code
  // or a language name in english (as used by XBMC)
  void SetSubtitleLanguage(const std::string& language);

  const std::string GetDVDMenuLanguage() const;
  const std::string GetDVDAudioLanguage() const;
  const std::string GetDVDSubtitleLanguage() const;
  const std::string& GetTimeZone() const;

  const std::string& GetRegionLocale() const;
  const std::string GetLanguageLocale(bool twochar = false) const;

  bool ForceUnicodeFont() const { return m_currentRegion->m_forceUnicodeFont; }

  const std::string& GetDateFormat(bool bLongDate=false) const;

  typedef enum _MERIDIEM_SYMBOL
  {
    MERIDIEM_SYMBOL_PM=0,
    MERIDIEM_SYMBOL_AM,
    MERIDIEM_SYMBOL_MAX
  } MERIDIEM_SYMBOL;

  const std::string& GetTimeFormat() const;
  const std::string& GetMeridiemSymbol(MERIDIEM_SYMBOL symbol) const;

  typedef enum _TEMP_UNIT
  {
    TEMP_UNIT_FAHRENHEIT=0,
    TEMP_UNIT_KELVIN,
    TEMP_UNIT_CELSIUS,
    TEMP_UNIT_REAUMUR,
    TEMP_UNIT_RANKINE,
    TEMP_UNIT_ROMER,
    TEMP_UNIT_DELISLE,
    TEMP_UNIT_NEWTON
  } TEMP_UNIT;

  const std::string& GetTempUnitString() const;
  CLangInfo::TEMP_UNIT GetTempUnit() const;


  typedef enum _SPEED_UNIT
  {
    SPEED_UNIT_KMH=0, // kilemetre per hour
    SPEED_UNIT_MPMIN, // metres per minute
    SPEED_UNIT_MPS, // metres per second
    SPEED_UNIT_FTH, // feet per hour
    SPEED_UNIT_FTMIN, // feet per minute
    SPEED_UNIT_FTS, // feet per second
    SPEED_UNIT_MPH, // miles per hour
    SPEED_UNIT_KTS, // knots
    SPEED_UNIT_BEAUFORT, // beaufort
    SPEED_UNIT_INCHPS, // inch per second
    SPEED_UNIT_YARDPS, // yard per second
    SPEED_UNIT_FPF // Furlong per Fortnight
  } SPEED_UNIT;

  const std::string& GetSpeedUnitString() const;
  CLangInfo::SPEED_UNIT GetSpeedUnit() const;

  void GetRegionNames(std::vector<std::string>& array);
  void SetCurrentRegion(const std::string& strName);
  const std::string& GetCurrentRegion() const;

  static bool CheckLanguage(const std::string& language);

  static void LoadTokens(const TiXmlNode* pTokens, std::vector<std::string>& vecTokens);

  static void SettingOptionsLanguagesFiller(const CSetting *setting, std::vector< std::pair<std::string, std::string> > &list, std::string &current, void *data);
  static void SettingOptionsStreamLanguagesFiller(const CSetting *setting, std::vector< std::pair<std::string, std::string> > &list, std::string &current, void *data);
  static void SettingOptionsRegionsFiller(const CSetting *setting, std::vector< std::pair<std::string, std::string> > &list, std::string &current, void *data);

protected:
  void SetDefaults();

  class CRegion
  {
  public:
    CRegion(const CRegion& region);
    CRegion();
    virtual ~CRegion();
    void SetDefaults();
    void SetTempUnit(const std::string& strUnit);
    void SetSpeedUnit(const std::string& strUnit);
    void SetTimeZone(const std::string& strTimeZone);
    void SetGlobalLocale();
    std::string m_strGuiCharSet;
    std::string m_strSubtitleCharSet;
    std::string m_strDVDMenuLanguage;
    std::string m_strDVDAudioLanguage;
    std::string m_strDVDSubtitleLanguage;
    std::string m_strLangLocaleName;
    std::string m_strLangLocaleCodeTwoChar;
    std::string m_strRegionLocaleName;
    bool m_forceUnicodeFont;
    std::string m_strName;
    std::string m_strDateFormatLong;
    std::string m_strDateFormatShort;
    std::string m_strTimeFormat;
    std::string m_strMeridiemSymbols[MERIDIEM_SYMBOL_MAX];
    std::string m_strTimeZone;

    TEMP_UNIT m_tempUnit;
    SPEED_UNIT m_speedUnit;
  };


  typedef std::map<std::string, CRegion> MAPREGIONS;
  typedef std::map<std::string, CRegion>::iterator ITMAPREGIONS;
  typedef std::pair<std::string, CRegion> PAIR_REGIONS;
  MAPREGIONS m_regions;
  CRegion* m_currentRegion; // points to the current region
  CRegion m_defaultRegion; // default, will be used if no region available via langinfo.xml

  std::string m_audioLanguage;
  std::string m_subtitleLanguage;
  // this is the general (not win32-specific) three char language code
  std::string m_languageCodeGeneral;
};


extern CLangInfo g_langInfo;
