function testNewScript() {

  // Get the spreadSheet
  const sheet = getSheet();

  // Get sheet data
  const data = getDataValues(sheet);
  Logger.log(data);


  // Check all the entries in the sheet for birthday
  checkForBirthday(data);

}


function getSheet() {
  return SpreadsheetApp.getActiveSpreadsheet().getActiveSheet();
}


function getDataValues(sheet) {
  return sheet.getDataRange().getValues();
}


function getTodaysDate() {
  return Utilities.formatDate(new Date(), Session.getScriptTimeZone(), "MM/dd");
}


function checkForBirthday(data) {
  for(let i = 1; i < data.length; i++) {
    const name = data[i][0];
    const email = data[i][1];
    const birthday = Utilities.formatDate(new Date(data[i][2]), Session.getScriptTimeZone(), "MM/dd");

    // Logger.log("Name: " + name + ", birthday: " + birthday + ", today: " + today);

    // Get today's date
    const today = getTodaysDate();

    if(today == birthday) {
      Logger.log("It's " + name + "'s birthday!");
      MailApp.sendEmail({
        to: email,
        subject: `Hey ${name}, I have an important message for you`,
        body: `This is a reminder to keep grinding and to get that first legal job!\nAlso, love you :)\n\nNafi`
      })      
    }

    Logger.log("Email sent successfully :)")
  }
}












