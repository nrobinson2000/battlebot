
var token = "0101e75a4acb0c906e1d8f4956f9cd032163db43";
var photon = "1d0028000b47343432313031";

var flspeed = "";
var frspeed = "";
var blspeed = "";
var brspeed = "";

var fldir = "";
var frdir = "";
var bldir = "";
var brdir = "";

var flcmd = "000";
var frcmd = "000";
var blcmd = "000";
var brcmd = "000";


function httpPost(url, params)
{
var xhr = new XMLHttpRequest();
xhr.open("POST", url, true);

//Send the proper header information along with the request
xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
xhr.setRequestHeader("Authorization", "Bearer " + token);
xhr.send(params);
}

function httpGet(theUrl)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open( "GET", theUrl, false ); // false for synchronous request
    xmlHttp.send( null );
    return xmlHttp.responseText;
}

function callFunction(device, functionName, args)
{
  var params = 'arg=' + args;
  console.clear()
  httpPost("https://api.particle.io/v1/devices/" + device + "/" + functionName, params);
  console.log("Called function: "+ functionName);
  console.log("On device: " + device);
  console.log("With arguments: " + args);
}

function makeProper(valueint)
{
  var value = valueint.toString();
  var valuedata = "";
  if (value.length == 2)
  {
        valuedata = value.toString();
  }

  if (value.length == 1)
  {
    valuedata = "0" + value.toString();
  }

  return valuedata;
}

function dummySlider(data)
{
  console.log("Slider Value = " + data);
  if (data > 51)
  {
    console.log("Forwards/Speed = " + (data - 51));
  }
  if (data < 51)
  {
    console.log("Backwards/Speed = " + (51 - data));
  }
  if (data == 51)
  {
    console.log("Stopping.  Speed = 0");
  }
}

function setfl(data)
{
  var tempdata = 0;
  if (data > 51)
  {
    fldir = "1";
    tempdata = data - 51;
  }
  if (data < 51)
  {
    fldir = "2";
    tempdata = 51 - data;
  }
  if (data == 51)
  {
    fldir = "0";
    tempdata = 0;
  }
  flcmd = fldir + makeProper(tempdata);
}

function setfr(data)
{
  var tempdata = 0;
  if (data > 51)
  {
    frdir = "1";
    tempdata = data - 51;
  }
  if (data < 51)
  {
    frdir = "2";
    tempdata = 51 - data;
  }
  if (data == 51)
  {
    frdir = "0";
    tempdata = 0;
  }
  frcmd = frdir + makeProper(tempdata);
}

function setbl(data)
{
  var tempdata = 0;
  if (data > 51)
  {
    bldir = "1";
    tempdata = data - 51;
  }
  if (data < 51)
  {
    bldir = "2";
    tempdata = 51 - data;
  }
  if (data == 51)
  {
    bldir = "0";
    tempdata = 0;
  }

  blcmd = bldir + makeProper(tempdata);
}

function setbr(data)
{
  var tempdata = 0;
  if (data > 51)
  {
    brdir = "1";
    tempdata = data - 51;
  }
  if (data < 51)
  {
    brdir = "2";
    tempdata = 51 - data;
  }
  if (data == 51)
  {
    brdir = "0";
    tempdata = 0;
  }
  brcmd = brdir + makeProper(tempdata);
}

function move()
{
  callFunction(photon, "move", flcmd+" "+frcmd+" "+blcmd+" "+ brcmd);
}

function reset()
{
    $("#flslider").val(51);
    $("#flslider").trigger('change');
    $("#frslider").val(51);
    $("#frslider").trigger('change');
    $("#blslider").val(51);
    $("#blslider").trigger('change');
    $("#brslider").val(51);
    $("#brslider").trigger('change');
    callFunction(photon, "move", "000 000 000 000");
}

console.log("To call any function use:");
console.log("callFunction(device, functionName, args)");